#pragma once

#include <assimp/material.h>
#include <sokol/sokol_gfx.h>
#include <glm/vec4.hpp>

#include <string>
#include <vector>
#include <optional>

namespace cruz
{
constexpr int MATERIAL_TEX_CHANNEL = 4;
class Material
{
  public:
    Material(const aiMaterial &, std::string);
    ~Material();

    std::optional<sg_image_desc> GetDiffuseTex() const;
    std::optional<glm::vec4> GetDiffuseCol() const;

  private:
    sg_image_desc LoadSGImage(std::string);
    
    std::optional<sg_image_desc> m_diffuse{};
    std::optional<glm::vec4> m_diffuseColor{};
    
    std::vector<unsigned char *> m_loadedImgs;
};
} // namespace cruz