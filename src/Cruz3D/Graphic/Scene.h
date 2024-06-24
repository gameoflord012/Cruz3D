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

static constexpr unsigned int AI_PROCESS_FLAGS = aiProcess_Triangulate | aiProcess_JoinIdenticalVertices;

class Scene
{
  public:
    Scene(const char *importPath);
    unique_ptrs<Material> GetMaterials();
    unique_ptrs<Mesh> GetMeshes();

  private:
    const char *m_fullPath;
    const aiScene *m_scene;
};
} // namespace cruz