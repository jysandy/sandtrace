#include "scene.hpp"
#include <iostream>

namespace sandtrace
{
    //Some helper functions to make the FBX file loading look more sane
    std::list<std::shared_ptr<triangle>>&& triangle_list_from_mesh(
        FbxNode*, FbxMesh*, std::shared_ptr<texture>, std::shared_ptr<material>);
    std::array<polygon_vertex, 3> triangle_vertices_from_mesh(FbxMesh*, int polygon_index);
    material material_from_node(FbxNode*);

    scene scene::from_fbx_file(std::string fbx_filename, std::string texname)
    {
        FbxManager* sdk_manager = FbxManager::Create();
        FbxIOSettings* ios = FbxIOSettings::Create(sdk_manager, IOSROOT);
        sdk_manager->SetIOSettings(ios);

        FbxImporter* importer = FbxImporter::Create(sdk_manager, "Importer");

        if (!importer->Initialize(fbx_filename.c_str(), -1, sdk_manager->GetIOSettings()))
        {
            throw std::runtime_error(importer->GetStatus().GetErrorString());
        }

        FbxScene* fbx_scene = FbxScene::Create(sdk_manager, "Scene");
        importer->Import(fbx_scene);
        importer->Destroy();

        FbxNode* root_node = fbx_scene->GetRootNode();
        if (!root_node)
        {
            throw std::runtime_error("Empty file: No mesh present");
        }

        scene new_scene;
        for (int i = 0; i < root_node->GetChildCount(); i++)
        {
            new_scene.build_mesh_list(root_node->GetChild(i), texname);
        }

        //Add the triangles to the primitive list.
        for (auto m : new_scene.meshes)
        {
            for (auto t : m.triangles)
            {
                new_scene.primitives.push_back(t);
            }
        }

        new_scene.cam = scene::default_camera();
        new_scene.directional_lights = scene::default_dlights();
        new_scene.point_lights = scene::default_plights();
        new_scene.spot_lights = scene::default_slights();

        sdk_manager->Destroy();

        return new_scene;
    }

    void scene::build_mesh_list(FbxNode* node, std::string texname)
    {
        FbxMesh* fbx_mesh = node->GetMesh();

        if (fbx_mesh)
        {

            FbxGeometryElementNormal* normals = fbx_mesh->GetElementNormal();
            FbxGeometryElementUV* uvs = fbx_mesh->GetElementUV();

            //DEFENSIVE CODE ALERT
            if (normals->GetMappingMode() != FbxLayerElement::eByPolygonVertex)
            {
                throw std::runtime_error("Unsupported mapping type of normal layer");
            }

            if (normals->GetReferenceMode() != FbxLayerElement::eDirect)
            {
                throw std::runtime_error("Unsupported reference mode of normal layer");
            }

            if (!uvs)
            {
                throw std::runtime_error("No UV mapping information available");
            }

            if (uvs->GetMappingMode() != FbxLayerElement::eByPolygonVertex)
            {
                throw std::runtime_error("Unsupported mapping type of UV layer");
            }

            if (uvs->GetReferenceMode() != FbxLayerElement::eIndexToDirect)
            {
                throw std::runtime_error("Unsupported reference mode of UV layer");
            }
            //END DEFENSIVE CODE

            //Read the material.
            auto mat = material_from_node(node);

            //Read the polygons.
            auto triangle_list = triangle_list_from_mesh(node, fbx_mesh, texpool.get(texname), std::make_shared<material>(mat));

            this->meshes.emplace_back(triangle_list, mat, texpool.get(texname));
        }

        for (int i = 0; i < node->GetChildCount(); i++)
        {
            build_mesh_list(node->GetChild(i), texname);
        }

    }

    std::list<std::shared_ptr<triangle>>&& triangle_list_from_mesh(
        FbxNode* node, FbxMesh* fbx_mesh, std::shared_ptr<texture> tex, std::shared_ptr<material> mat)
    {
        FbxAMatrix& mesh_matrix = node->EvaluateGlobalTransform();
        glm::mat4 transform;
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                transform[j][i] = mesh_matrix.Get(i, j);    //From row-major to column-major
            }
        }
        transform = glm::mat4(1.0f);

        std::list<std::shared_ptr<triangle>> ret;
        for (int polygon_index = 0; polygon_index < fbx_mesh->GetPolygonCount(); polygon_index++)
        {
            auto vertices = triangle_vertices_from_mesh(fbx_mesh, polygon_index);

            //Need to transform the vertices!
            for (auto& v : vertices)
            {
                v.position = glm::vec3(transform * glm::vec4(v.position, 1.0f));
                v.normal = glm::vec3(transform * glm::vec4(v.normal, 0.0f));
            }

            ret.emplace_back(std::make_shared<triangle>(
                vertices[0], vertices[1], vertices[2], tex, mat
            ));
        }

        return std::move(ret);
    }

    std::array<polygon_vertex, 3> triangle_vertices_from_mesh(FbxMesh* fbx_mesh, int polygon_index)
    {
        auto polygon_size = fbx_mesh->GetPolygonSize(polygon_index);
        if (polygon_size != 3)
        {
            throw std::runtime_error("Found a polygon which is not a triangle");
        }

        std::array<polygon_vertex, 3> ret;
        for (int vertex_position = 0; vertex_position < polygon_size; vertex_position++)
        {
            polygon_vertex vertex;

            auto control_points = fbx_mesh->GetControlPoints();
            auto control_point_index = fbx_mesh->GetPolygonVertex(polygon_index, vertex_position);
            auto control_point = control_points[control_point_index];
            for (int i = 0; i < 3; i++)
            {
                vertex.position[i] = control_point[i];
            }

            FbxVector4 norm;
            fbx_mesh->GetPolygonVertexNormal(polygon_index, vertex_position, norm);
            for (int i = 0; i < 3; i++)
            {
                vertex.normal[i] = control_point[i];
            }

            FbxVector2 tex;
            bool mapped;
            auto uv_set_name = fbx_mesh->GetElementUV()->GetName();
            fbx_mesh->GetPolygonVertexUV(polygon_index, vertex_position, uv_set_name, tex, mapped);
            vertex.texcoord.x = tex[0];
            vertex.texcoord.y = 1 - tex[1];

            ret[vertex_position] = vertex;
        }

        return ret;
    }

    material material_from_node(FbxNode* node)
    {
        auto mat = node->GetMaterial(0);
        if (!mat)
        {
            throw std::runtime_error("No material found for a mesh");
        }

        if (!mat->Is<FbxSurfacePhong>())
        {
            throw std::runtime_error("Material found is not a Phong material");
        }

        FbxSurfacePhong* phong_surface = reinterpret_cast<FbxSurfacePhong*>(mat);

        glm::vec4 ambient, diffuse, specular;
        ambient.w = diffuse.w = specular.w = 1;
        for (int i = 0; i < 3; i++)
        {
            ambient[i] = phong_surface->Ambient.Get()[i];
            diffuse[i] = phong_surface->Diffuse.Get()[i];
            specular[i] = phong_surface->Specular.Get()[i];
        }

        return std::move(material(
            ambient, diffuse, specular,
            phong_surface->Shininess.Get(),
            0   //TODO: Get the reflectance from the FBX file if possible
        ));
    }

    camera scene::default_camera()
    {
        auto look_from = glm::vec3(0.0f, 10.0f, 0.0f);
        auto look_at = glm::vec3(0.0f, 0.0f, 0.0f);
        auto up = glm::vec3(0, 1, 0);
        auto fov = glm::half_pi<float>();

        return camera(look_from, look_at, up, fov);
    }

    std::vector<directional_light> scene::default_dlights()
    {
        //Two directional lights.

        auto ambient = glm::vec4(0.1, 0.1, 0.1, 1.0);
        auto diffuse = glm::vec4(0.7, 0.7, 0.7, 1.0);
        auto specular = glm::vec4(0.2, 0.2, 0.2, 1.0);

        auto direction1 = glm::vec3(1, -1, 1);
        auto direction2 = glm::vec3(-1, -1, -1);

        return std::vector<directional_light>{
            {ambient, diffuse, specular, direction1},
            {ambient, diffuse, specular, direction2}
        };
    }

    std::vector<point_light> scene::default_plights()
    {
        //No point lights.
        return std::vector<point_light>();
    }

    std::vector<spot_light> scene::default_slights()
    {
        //No spot lights.
        return std::vector<spot_light>();
    }

}
