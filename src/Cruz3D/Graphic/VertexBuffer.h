#pragma once

#include <assimp/color4.h>
#include <assimp/vector3.h>
#include <initializer_list>
#include <sokol_gfx.h>
#include <vector>

namespace cruz
{
class VertexBuffer
{
  public:
    void Push(const aiVector3D &v3);
    void Push(const aiColor4D &col);
    sg_range GetRange() const;

  private:
    typedef float vertex_t;
    std::vector<vertex_t> m_data{};
};
} // namespace cruz
