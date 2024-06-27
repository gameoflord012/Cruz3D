#include "SimpleBinding.h"

#include "../Material.h"
#include "../Mesh.h"
#include "../SokolHelpers.inl"

cruz::SimpleBinding::SimpleBinding(const Mesh &mesh, const Material &mat)
{
    m_image = sg_make_image(mat.GetDiffuse());

    // create a sampler object
    m_sampler = sg_make_sampler({
        .min_filter = SG_FILTER_LINEAR,
        .mag_filter = SG_FILTER_LINEAR,
    });

    m_vbuf = cruz::make_vertex_buffer(mesh.GetVBuf());
    m_ibuf = cruz::make_index_buffer(mesh.GetIBuf());

    m_bindings = {.vertex_buffers = {m_vbuf},
                  .index_buffer = m_ibuf,
                  .fs = {
                      .images = {m_image},
                      .samplers = {m_sampler},
                  }};

    m_numIndicies = mesh.GetIBuf().count();
}

cruz::SimpleBinding::~SimpleBinding()
{
    sg_dealloc_buffer(m_vbuf);
    sg_dealloc_buffer(m_ibuf);
    sg_dealloc_sampler(m_sampler);
    sg_dealloc_image(m_image);
}

const unsigned int cruz::SimpleBinding::GetNumIndicies() const
{
    return m_numIndicies;
}

const sg_bindings &cruz::SimpleBinding::GetSGBindings() const
{
    return m_bindings;
}
