#pragma once

#include <sokol/sokol_gfx.h>

namespace cruz
{
class Mesh;
class Material;

class SimpleBinding
{
  public:
    SimpleBinding(const Mesh &mesh, const Material &mat);
    ~SimpleBinding();

    const unsigned int GetNumIndicies() const;
    const sg_bindings &GetSGBindings() const;

  private:
    unsigned int m_numIndicies;
    sg_bindings m_bindings;
    sg_image m_image;
    sg_sampler m_sampler;
    sg_buffer m_ibuf, m_vbuf;
};
} // namespace cruz