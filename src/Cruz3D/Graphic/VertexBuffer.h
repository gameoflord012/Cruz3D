#pragma once

#include <assimp/color4.h>
#include <assimp/vector2.h>
#include <assimp/vector3.h>

#include <sokol/sokol_gfx.h>

#include <initializer_list>
#include <vector>

namespace cruz
{
class VertexBuffer
{
  public:
    void Push(const aiVector3D &v3);
    void Push(const aiVector2D &v2);
    void Push(const aiColor4D &col);
    sg_range GetRange() const;

  private:
    typedef float vertex_t;
    std::vector<vertex_t> m_data{};
};
} // namespace cruz
