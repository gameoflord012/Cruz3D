#ifndef CRUZ_SHADER_H
#define CRUZ_SHADER_H
#include <sokol_gfx.h>
namespace cruz
{
sg_shader make_shader(const char *shaderName);
}
#endif // !CRUZ_SHADER_H

// ██╗███╗░░░███╗██████╗░██╗░░░░░███████╗███╗░░░███╗███████╗███╗░░██╗████████╗░█████╗░████████╗██╗░█████╗░███╗░░██╗
// ██║████╗░████║██╔══██╗██║░░░░░██╔════╝████╗░████║██╔════╝████╗░██║╚══██╔══╝██╔══██╗╚══██╔══╝██║██╔══██╗████╗░██║
// ██║██╔████╔██║██████╔╝██║░░░░░█████╗░░██╔████╔██║█████╗░░██╔██╗██║░░░██║░░░███████║░░░██║░░░██║██║░░██║██╔██╗██║
// ██║██║╚██╔╝██║██╔═══╝░██║░░░░░██╔══╝░░██║╚██╔╝██║██╔══╝░░██║╚████║░░░██║░░░██╔══██║░░░██║░░░██║██║░░██║██║╚████║
// ██║██║░╚═╝░██║██║░░░░░███████╗███████╗██║░╚═╝░██║███████╗██║░╚███║░░░██║░░░██║░░██║░░░██║░░░██║╚█████╔╝██║░╚███║
// ╚═╝╚═╝░░░░░╚═╝╚═╝░░░░░╚══════╝╚══════╝╚═╝░░░░░╚═╝╚══════╝╚═╝░░╚══╝░░░╚═╝░░░╚═╝░░╚═╝░░░╚═╝░░░╚═╝░╚════╝░╚═╝░░╚══╝

#ifdef CRUZ_IMPL

#define SHADERDESC_IMPL
#include "ShaderDesc.h"
#undef SHADERDESC_IMPL

#include <cassert>
#include <string>
#include <unordered_map>

#define NAMEOF(x) #x

namespace cruz
{
static std::unordered_map<std::string, sg_shader> Shaders{};

sg_shader make_shader(const char *shaderName)
{
    if (Shaders.find(shaderName) == Shaders.end())
    {
        // shaderName must in Descs
        assert(ShaderDesc::Descs.find(shaderName) != ShaderDesc::Descs.end());
        Shaders[shaderName] = sg_make_shader(ShaderDesc::Descs[shaderName]);
    }
    return Shaders[shaderName];
}
} // namespace cruz

#undef NAMEOF
#endif
