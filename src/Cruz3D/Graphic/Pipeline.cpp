
#include "Pipeline.h"

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
					},
					{
						.format = SG_VERTEXFORMAT_FLOAT2 // texture coordinate
					}
				}
			},
			.depth = {
				.compare = SG_COMPAREFUNC_LESS_EQUAL,
				.write_enabled = true,
			},
			.index_type = SG_INDEXTYPE_UINT32,
			.cull_mode = SG_CULLMODE_BACK,
		}; // clang-format on

		m_pip = sg_make_pipeline(desc);
	}

	Pipeline::~Pipeline()
	{
		sg_dealloc_pipeline(m_pip);
	}

	sg_pipeline Pipeline::GetSGPipeline() const
	{
		return m_pip;
	}
} // namespace cruz
