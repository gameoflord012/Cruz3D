#include "Material.h"

#include <stb/stb_image.h>

#include <cassert>


cruz::Material::Material(const aiMaterial &mat, std::string dir)
{
    if(mat.GetTextureCount(aiTextureType_DIFFUSE) > 0)
    {
        aiString texPath;
        assert(mat.GetTexture(aiTextureType_DIFFUSE, 0, &texPath) == aiReturn_SUCCESS);
        dir = dir + '/' + texPath.C_Str();
        (void)dir;
    }
}
