#pragma once

#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <vector>
#include <memory>

namespace cruz
{
class Mesh;
class Material;

template<typename T>
using unique_ptrs = std::vector<std::unique_ptr<T>>;

static constexpr unsigned int AI_PROCESS_FLAGS = aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_FlipUVs;

class Scene
{
  public:
    Scene(const char *importPath);
    unique_ptrs<Material> GetMaterials() const;
    unique_ptrs<Mesh> GetMeshes() const;

  private:
    const char *m_fullPath;
    const aiScene *m_scene;
};
} // namespace cruz