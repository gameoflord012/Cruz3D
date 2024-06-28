#include "SimpleBinding.h"

#include "../Material.h"
#include "../Mesh.h"
#include "../SokolHelpers.inl"

#include <glm/vec4.hpp>

cruz::SimpleBinding::SimpleBinding(const Mesh &mesh, const Material &mat)
{
    // diffuse texture
    if (mat.GetDiffuseTex().has_value())
    {
        m_image = sg_make_image(mat.GetDiffuseTex().value());
    }
    else
    {
        unsigned char ptr[4]{255, 255, 255, 255};

        sg_image_desc singleWhitePixel = {.width = 1, .height = 1, .pixel_format = SG_PIXELFORMAT_RGBA8};
        singleWhitePixel.data.subimage[0][0] = {.ptr = ptr, .size = sizeof(ptr)};
        m_image = sg_make_image(singleWhitePixel);
    }

    // create a sampler object
    m_sampler = sg_make_sampler({
        .min_filter = SG_FILTER_LINEAR,
        .mag_filter = SG_FILTER_LINEAR,
        .wrap_u = SG_WRAP_REPEAT,
        .wrap_v = SG_WRAP_REPEAT,
    });

    Material_FS_Uniforms fs_uniforms =
    {
        .diffuseColor = mat.GetDiffuseCol().value_or(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f))
    };

    m_vbuf = cruz::make_vertex_buffer(mesh.GetVBuf());
    m_ibuf = cruz::make_index_buffer(mesh.GetIBuf());
    m_numIndicies = mesh.GetIBuf().count();
    m_sbuf = cruz::make_storage_buffer(SG_RANGE(fs_uniforms));

    // clang-format off
    m_bindings = 
    {
        .vertex_buffers = {m_vbuf},
        .index_buffer = m_ibuf,
        .fs = 
        {
            .images = {m_image}, 
            .samplers = {m_sampler}, 
            .storage_buffers = {m_sbuf}
        }};
    // clang-format on
}

cruz::SimpleBinding::~SimpleBinding()
{
    sg_dealloc_buffer(m_vbuf);
    sg_dealloc_buffer(m_ibuf);
    sg_dealloc_buffer(m_sbuf);
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
