#pragma once

#include "VertexBuffer.h"
#include "IndexBuffer.h"

#include <sokol/sokol_gfx.h>

namespace cruz
{
inline sg_buffer make_vertex_buffer(const VertexBuffer& buffer)
{
    return sg_make_buffer({.data = buffer.GetRange()});
}

inline sg_buffer make_index_buffer(const IndexBuffer& buffer)
{
    return sg_make_buffer({.type = SG_BUFFERTYPE_INDEXBUFFER, .data = buffer.GetRange()});
}
} // namespace cruz