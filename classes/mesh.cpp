#include "mesh.hpp"

#include <fbxsdk.h>
#include <exception>
#include <stdexcept>

namespace sandtrace
{
    static mesh mesh::from_fbx_file(std::string filename)
    {
        FbxManager* sdk_manager = FbxManager::Create();
        FbxIOSettings* ios = FbxIOSettings::Create(sdkManager, IOSROOT);
        sdkManager->SetIOSettings(ios);

        FbxImporter* importer = FbxImporter::Create(sdk_manager, "Importer");

        if (!importer->Initialize(filename.c_str(), -1, sdk_manager->GetIOSettings()))
        {
            throw std::exception(importer->GetStatus().GetErrorString());
        }

        FbxScene* scene = FbxScene::Create(sdkManager, "Scene");
        importer->Import(scene);
        importer->Destroy();

        FbxNode* root_node = scene->GetRootNode();
        if (!root_node)
        {
            throw std::exception("Empty file: No mesh present");
        }

        FbxMesh* fbx_mesh = root_node->GetMesh();
        if (!mesh)
        {
            throw std::exception("Error: No mesh found");
        }


    }
}
