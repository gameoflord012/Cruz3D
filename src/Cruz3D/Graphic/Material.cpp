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

        Load_sg_image(m_diffuse, dir + '/' + texPath.C_Str());
    }
}

cruz::Material::~Material()
{
    sg_dealloc_image(m_diffuse);
}

sg_image cruz::Material::GetDiffuse() const
{
    return m_diffuse;
}

void cruz::Material::Load_sg_image(sg_image &img, std::string path)
{
    int width, height, channel;
    stbi_uc *tex = stbi_load(path.c_str(), &width, &height, &channel, MATERIAL_TEX_CHANNEL);
    if (tex == NULL)
    {
        DEBUG(stbi_failure_reason());
        assert(false);
    }

    sg_image_desc imgDesc = {
        .width = width,
        .height = height,
        .pixel_format = SG_PIXELFORMAT_RGBA8,
    };
    imgDesc.data.subimage[0][0] = {.ptr = tex, .size = sizeof(stbi_uc) * width * height * 4};
    img = sg_make_image(imgDesc);

    stbi_image_free(tex);
}
