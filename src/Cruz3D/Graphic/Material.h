#pragma once

#include <assimp/material.h>
#include <sokol/sokol_gfx.h>

#include <string>
#include <vector>

namespace cruz
{
constexpr int MATERIAL_TEX_CHANNEL = 4;
class Material
{
  public:
    Material(const aiMaterial &, std::string);
    ~Material();

    sg_image_desc GetDiffuse() const;

  private:
    sg_image_desc LoadSGImage(std::string);
    sg_image_desc m_diffuse{};
    std::vector<unsigned char *> m_loadedImgs;
};
} // namespace cruz