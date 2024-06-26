#pragma once

#include <sokol/sokol_gfx.h>

namespace cruz
{
class Pipeline
{
  public:
    Pipeline(sg_shader);
    ~Pipeline();

    sg_pipeline sg_pip() const;

  private:
    sg_pipeline m_pip{};
};
} // namespace cruz