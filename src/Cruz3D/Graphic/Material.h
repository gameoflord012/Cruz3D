#pragma once

#include <assimp/material.h>

#include <string>

namespace cruz
{
class Material
{
  public:
    Material(const aiMaterial &, std::string);

  private:
    char *m_diffuseTex{};
};
} // namespace cruz