#include "VertexBuffer.h"

#include <cassert>

namespace cruz
{
void VertexBuffer::Push(const aiVector3D &v3)
{
    m_data.push_back(v3.x);
    m_data.push_back(v3.y);
    m_data.push_back(v3.z);
}

void VertexBuffer::Push(const aiColor4D &col)
{
    m_data.push_back(col.r);
    m_data.push_back(col.g);
    m_data.push_back(col.b);
    m_data.push_back(col.a);
}

sg_range VertexBuffer::GetRange() const
{
    sg_range rg = {.ptr = m_data.data(), .size = m_data.size() * sizeof(vertex_t)};
    return rg;
    }
} // namespace cruz
