#pragma once

#include <assimp/material.h>
#include <sokol/sokol_gfx.h>

#include <string>

namespace cruz
{
constexpr int MATERIAL_TEX_CHANNEL = 4;

class Material
{
  public:
    Material(const aiMaterial &, std::string);
    ~Material();

    sg_image GetDiffuse() const;

  private:
    void Load_sg_image(sg_image &, std::string);

    sg_image m_diffuse{};
};
} // namespace cruz