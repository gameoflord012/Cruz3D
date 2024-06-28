#include "Scene.h"

#include "Importer.h"
#include "Material.h"
#include "Mesh.h"
#include "Cruz3D/Debug.h"
#include "Cruz3D/Ultility/FileHelper.inl"

#include <string>
#include <cassert>

namespace cruz
{
Scene::Scene(const char *importPath)
{
    m_scene = singleton::Importer.ReadFile(importPath, AI_PROCESS_FLAGS);
    m_fullPath = importPath;

    if (!m_scene)
    {
        DEBUG(singleton::Importer.GetErrorString());
        assert(false);
    }
}

unique_ptrs<Material> Scene::GetMaterials() const
{
    unique_ptrs<Material> mats;
    std::string dir = GetDir(m_fullPath);

    for(unsigned int i = 0; i < m_scene->mNumMaterials; i++)
    {
        const aiMaterial *mat = m_scene->mMaterials[i];
        mats.push_back(std::make_unique<Material>(*mat, dir));
    }

    return mats;
}

unique_ptrs<Mesh> Scene::GetMeshes() const
{
    unique_ptrs<Mesh> meshes;

    for(unsigned int i = 0; i < m_scene->mNumMeshes; i++)
    {
        const aiMesh *m = m_scene->mMeshes[i];
        meshes.push_back(std::make_unique<Mesh>(*m));
    }

    return meshes;
}
} // namespace cruz