#include "Material.h"

#include <stb/stb_image.h>

#include <Cruz3D/Debug.h>
#include <cassert>

cruz::Material::Material(const aiMaterial &mat, std::string dir)
{
    if (mat.GetTextureCount(aiTextureType_DIFFUSE) > 0)
    {
        aiString texPath;
        assert(mat.GetTexture(aiTextureType_DIFFUSE, 0, &texPath) == aiReturn_SUCCESS);
        m_diffuse = LoadSGImage(dir + '/' + texPath.C_Str());
    }

    aiColor4D diffuseCol;
    assert(aiGetMaterialColor(&mat, AI_MATKEY_COLOR_DIFFUSE, &diffuseCol) == aiReturn_SUCCESS);
    m_diffuseColor = {diffuseCol.r, diffuseCol.g, diffuseCol.b, diffuseCol.a};
}

cruz::Material::~Material()
{
    for (auto img : m_loadedImgs)
    {
        stbi_image_free(img);
    }
}

std::optional<sg_image_desc> cruz::Material::GetDiffuseTex() const
{
    return m_diffuse;
}

std::optional<glm::vec4> cruz::Material::GetDiffuseCol() const
{
    return m_diffuseColor;
}

sg_image_desc cruz::Material::LoadSGImage(std::string path)
{
    // load image with stb
    int width, height, channel;
    stbi_uc *tex = stbi_load(path.c_str(), &width, &height, &channel, MATERIAL_TEX_CHANNEL);
    if (tex == NULL)
    {
        DEBUG(stbi_failure_reason());
        assert(false);
    }

    // for releasing resource later
    m_loadedImgs.push_back(tex);

    // init image_desc
    sg_image_desc imgDesc = {
        .width = width,
        .height = height,
        .pixel_format = SG_PIXELFORMAT_RGBA8,
    };

    imgDesc.data.subimage[0][0] = {.ptr = tex, .size = sizeof(stbi_uc) * width * height * 4};
    return imgDesc;
}
