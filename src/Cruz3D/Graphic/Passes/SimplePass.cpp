#include "SimplePass.h"

#include "../Shader.h"

#include <sokol/sokol_gfx.h>
#include <sokol/sokol_glue.h>

#include <cassert>

cruz::SimplePass::SimplePass()
{
    m_pip = new cruz::Pipeline(cruz::make_shader("BasicMVP"));
}

void cruz::SimplePass::Begin()
{
    assert(!m_shouldEnd);
    m_shouldEnd = true;

    sg_begin_pass({.swapchain = sglue_swapchain()});
    sg_apply_pipeline(m_pip->GetSGPipeline());
}

void cruz::SimplePass::End()
{
    assert(m_shouldEnd);
    m_shouldEnd = false;
    
    sg_end_pass();
}

void cruz::SimplePass::ApplyVSUniform(const ShaderDesc::BasicMVP_VS_Uniform &params)
{
    sg_apply_uniforms(SG_SHADERSTAGE_VS, 0, SG_RANGE(params));
}

void cruz::SimplePass::ApplyBinding(const SimpleBinding *binding)
{
    m_currentBinding = binding;
    sg_apply_bindings(binding->GetSGBindings());
}

void cruz::SimplePass::Draw()
{
    sg_draw(0, m_currentBinding->GetNumIndicies(), 1);
}
