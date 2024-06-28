#ifndef SHADERDESCS_H
#define SHADERDESCS_H

#include <glm/gtc/matrix_transform.hpp>
#include <sokol/sokol_gfx.h>
#include <string>

namespace cruz
{
namespace ShaderDesc
{
struct BasicMVP_VS_Uniforms
{
    glm::mat4x4 mvp;
};
} // namespace ShaderDesc
} // namespace cruz
#endif // !SHADERDESCS_H

// ██╗███╗░░░███╗██████╗░██╗░░░░░███████╗███╗░░░███╗███████╗███╗░░██╗████████╗░█████╗░████████╗██╗░█████╗░███╗░░██╗
// ██║████╗░████║██╔══██╗██║░░░░░██╔════╝████╗░████║██╔════╝████╗░██║╚══██╔══╝██╔══██╗╚══██╔══╝██║██╔══██╗████╗░██║
// ██║██╔████╔██║██████╔╝██║░░░░░█████╗░░██╔████╔██║█████╗░░██╔██╗██║░░░██║░░░███████║░░░██║░░░██║██║░░██║██╔██╗██║
// ██║██║╚██╔╝██║██╔═══╝░██║░░░░░██╔══╝░░██║╚██╔╝██║██╔══╝░░██║╚████║░░░██║░░░██╔══██║░░░██║░░░██║██║░░██║██║╚████║
// ██║██║░╚═╝░██║██║░░░░░███████╗███████╗██║░╚═╝░██║███████╗██║░╚███║░░░██║░░░██║░░██║░░░██║░░░██║╚█████╔╝██║░╚███║
// ╚═╝╚═╝░░░░░╚═╝╚═╝░░░░░╚══════╝╚══════╝╚═╝░░░░░╚═╝╚══════╝╚═╝░░╚══╝░░░╚═╝░░░╚═╝░░╚═╝░░░╚═╝░░░╚═╝░╚════╝░╚═╝░░╚══╝

#ifdef SHADERDESC_IMPL

namespace cruz
{
namespace ShaderDesc
{
static std::unordered_map<std::string, sg_shader_desc> Descs{
    // clang-format off
    {
        "BasicMVP",
        {
            .vs
            {
                .source = R"(
#version 460

uniform mat4 mvp;
layout(location=0) in vec4 position;
layout(location=1) in vec4 color0;
layout(location=2) in vec2 texcoord0;

out vec4 color;
out vec2 uv;

void main() {
    gl_Position =  mvp * position;
    color = color0;
    uv = texcoord0;
}
)",

                .uniform_blocks 
                {
                    {
                        .size = sizeof(BasicMVP_VS_Uniforms),
                        .uniforms = {{.name = "mvp", .type = SG_UNIFORMTYPE_MAT4}}
                    }
                }
            },

            .fs 
            {
                .source = R"(
#version 460

uniform sampler2D tex;
layout (binding = 8) buffer Material
{
    vec4 diffuseColor;
};

in vec4 color;
in vec2 uv;

out vec4 frag_color;

void main() {
    frag_color = texture(tex, uv) * color * diffuseColor;
}
)",
                
                .storage_buffers { { .used = true, .readonly = true } },
                .images { { .used = true } },
                .samplers { { .used = true } },
                .image_sampler_pairs { { .used = true, .image_slot = 0, .sampler_slot = 0, .glsl_name = "tex" } },
            }
        }
    },
    #ifdef ADDITIONAL_SHADER_DESCS
    ADDITIONAL_SHADER_DESCS
    #endif
    // clang-format on
};
} // namespace ShaderDesc
} // namespace cruz

#endif // SHADERDESC_IMPL