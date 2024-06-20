#pragma once

#include "ShaderDesc.h"

#include <sokol_gfx.h>
#include <unordered_map>

#define NAMEOF(x) #x

namespace cruz
{
inline sg_shader make_shader(const char *shaderName)
{
    static std::unordered_map<const char *, sg_shader> shaders{};
    if (shaders.find(shaderName) == shaders.end())
    {
        if (strcmp(shaderName, NAMEOF(BasicMVP)) == 0)
        {
            shaders[shaderName] = sg_make_shader(ShaderDesc::BasicMVP);
        }
    }

    return shaders[shaderName];
}
} // namespace cruz