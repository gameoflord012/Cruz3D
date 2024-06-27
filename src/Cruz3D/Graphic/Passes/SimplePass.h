#pragma once

#include "../Pipeline.h"
#include "../ShaderDesc.h"
#include "SimpleBinding.h"

namespace cruz
{
class SimplePass
{
  public:
    SimplePass();

    void Begin();
    void End();

    void ApplyVSUniform(const ShaderDesc::BasicMVP_VS_Uniform &);
    void ApplyBinding(const SimpleBinding *);
    void Draw();

  private:
    Pipeline *m_pip;
    const SimpleBinding *m_currentBinding{};
    bool m_shouldEnd{};
};
} // namespace cruz