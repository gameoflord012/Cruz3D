#include "Pipeline.h"
#include "Settings.h"

namespace cruz
{
Pipeline::Pipeline(sg_shader shader)
{
    // clang-format off
    sg_pipeline_desc desc
    {
        .shader = shader,
        .layout = {
            .attrs = {
                {
                    .format = SG_VERTEXFORMAT_FLOAT3 // vertex position
                },
                {
                    .format = SG_VERTEXFORMAT_FLOAT4 // vertex color
                }
            }
        },
        .depth = {
            .compare = SG_COMPAREFUNC_LESS_EQUAL,
            .write_enabled = false,
        },
        .index_type = cruz::INDEXBUFFER_TYPE,
        .cull_mode = SG_CULLMODE_BACK,
    }; // clang-format on

    m_pip = sg_make_pipeline(desc);
}

Pipeline::~Pipeline()
{
    sg_dealloc_pipeline(m_pip);
}
sg_pipeline Pipeline::sg_pip() const
{
    return m_pip;
}
} // namespace cruz
