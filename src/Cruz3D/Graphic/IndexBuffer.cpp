#include "IndexBuffer.h"

#include <assert.h>

namespace cruz
{
void IndexBuffer::Push(const aiFace &face)
{
    assert(face.mNumIndices == 3); // a triangle face
    m_data.push_back(face.mIndices[0]);
    m_data.push_back(face.mIndices[1]);
    m_data.push_back(face.mIndices[2]);
}
sg_range IndexBuffer::GetRange() const
{
    sg_range rg = { .ptr = m_data.data(), .size = m_data.size() * sizeof(index_t)};
    return rg;
}
size_t IndexBuffer::count() const
{
    return m_data.size();
}
} // namespace cruz