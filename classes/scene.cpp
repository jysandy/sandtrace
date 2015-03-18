#include "scene.hpp"

namespace sandtrace
{
    scene scene::from_fbx_file(std::string fbx_filename)
    {
        FbxManager* sdk_manager = FbxManager::Create();
        FbxIOSettings* ios = FbxIOSettings::Create(sdk_manager, IOSROOT);
        sdk_manager->SetIOSettings(ios);

        FbxImporter* importer = FbxImporter::Create(sdk_manager, "Importer");

        if (!importer->Initialize(fbx_filename.c_str(), -1, sdk_manager->GetIOSettings()))
        {
            throw std::runtime_error(importer->GetStatus().GetErrorString());
        }

        FbxScene* scene = FbxScene::Create(sdk_manager, "Scene");
        importer->Import(scene);
        importer->Destroy();

        FbxNode* root_node = scene->GetRootNode();
        if (!root_node)
        {
            throw std::runtime_error("Empty file: No mesh present");
        }

        scene new_scene;
        for (int i = 0; i < root_node->GetChildCount(); i++)
        {
            new_scene.build_mesh_list(root_node->GetChild(i)));
        }

        new_scene.cam = scene::default_camera();
        new_scene.directional_lights = scene::default_dlights();
        new_scene.point_lights = scene::default_plights();
        new_scene.spot_lights = scene::default_slights();

        return new_scene;
    }

    void scene::build_mesh_list(FbxNode* node)
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

            FbxAMatrix& mesh_matrix = node->EvaluateGlobalTransform();
            glm::mat4 transform;
            for (int i = 0; i < 4; i++)
            {
                for (int j = 0; j < 4; j++)
                {
                    transform[j][i] = mesh_matrix.Get(i, j);    //From row-major to column-major
                }
            }

            auto uv_set_name = uvs->GetName();
            auto control_points = fbx_mesh->GetControlPoints();
            auto control_indices = fbx_mesh->GetPolygonVertices();
            auto normal_array = normals->GetDirectArray();
            auto normal_index_array = normals->GetIndexArray();
            auto uv_array = uvs->GetDirectArray();
            auto uv_index_array = uvs->GetIndexArray();

            auto new_mesh = std::make_shared<mesh>();

            //Read the polygons
            for (int polygon_index = 0; polygon_index < fbx_mesh->GetPolygonCount(); polygon_index++)
            {
                auto polygon_size = fbx_mesh->GetPolygonSize(polygon_index);
                if (polygon_size != 3)
                {
                    throw std::runtime_error("Found a polygon which is not a triangle");
                }

                auto new_triangle = std::make_shared<triangle>(new_mesh);
                for (int vertex_position = 0; vertex_position < polygon_size; vertex_position++)
                {
                    polygon_vertex vertex;

                    auto control_point_index = fbx_mesh->GetPolygonVertex(polygon_index, vertex_position);
                    auto control_point = control_points[control_point_index];
                    glm::vec3 temp;
                    for (int i = 0; i < 3; i++)
                    {
                        temp[i] = control_point[i];
                    }
                    temp = glm::vec3(transform * glm::vec4(temp, 1.0f));
                    vertex.position = temp;

                    FbxVector4 norm;
                    fbx_mesh->GetPolygonVertexNormal(polygon_index, vertex_position, norm);
                    for (int i = 0; i < 3; i++)
                    {
                        temp[i] = control_point[i];
                    }
                    temp = glm::vec3(transform * glm::vec4(temp, 0.0f));
                    vertex.normal = temp;

                    FbxVector2 tex;
                    bool mapped;
                    fbx_mesh->GetPolygonVertexUV(polygon_index, vertex_position, uv_set_name, tex, mapped);
                    vertex.texcoord.x = tex[0];
                    vertex.texcoord.y = 1 - tex[1];

                    new_triangle->vertices[vertex_position] = vertex;
                }
                this->primitives.push_back(new_triangle);
                new_mesh->triangles.push_back(new_triangle);
            }

            //Read the material
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
            material foo;
            for (int i = 0; i < 3; i++)
            {
                foo.ambient[i] = phong_surface->Ambient.Get()[i];
                foo.diffuse[i] = phong_surface->Diffuse.Get()[i];
                foo.specular[i] = phong_surface->Specular.Get()[i];
            }
            foo.ambient.w = 1;
            foo.diffuse.w = 1;
            foo.specular.w = 1;

            foo.shininess = phong_surface->Shininess.Get();
            foo.reflectance = 0;    //TODO: Get the reflectance from the FBX file if possible

            new_mesh->mat = foo;
            this->meshes.push_back(new_mesh);
        }

        for (int i = 0; i < node->GetChildCount(); i++)
        {
            build_mesh_list(node->GetChild(i)));
        }

    }
}
