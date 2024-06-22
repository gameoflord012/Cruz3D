#pragma once

#include <assimp/mesh.h>
#include <sokol_gfx.h>
#include <vector>
#include <utility>


namespace cruz
{
class IndexBuffer
{
  public:
    void Push(const aiFace &face);
    sg_range GetRange() const;
    size_t count() const;

  private:
    typedef unsigned int index_t;
    std::vector<index_t> m_data;
};
} // namespace cruz