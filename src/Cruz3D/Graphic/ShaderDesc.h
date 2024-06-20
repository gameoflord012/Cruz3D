#ifndef SHADERDESCS_H
#define SHADERDESCS_H

#include <glm/gtc/matrix_transform.hpp>
#include <sokol_gfx.h>
#include <string>

namespace cruz
{
namespace ShaderDesc
{
struct BasicMVP_uniform
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
                .source = 
                    "#version 330\n"
                    "uniform mat4 mvp;\n"
                    "layout(location=0) in vec4 position;\n"
                    "layout(location=1) in vec4 color0;\n"
                    "out vec4 color;\n"
                    "void main() {\n"
                    "  gl_Position = mvp * position;\n"
                    "  color = color0;\n"
                    "}\n",

                .uniform_blocks 
                {
                    {
                        .size = sizeof(BasicMVP_uniform),
                        .uniforms = {{.name = "mvp", .type = SG_UNIFORMTYPE_MAT4}}
                    }
                }
            },

            .fs 
            {
                .source =   
                    "#version 330\n"
                    "in vec4 color;\n"
                    "out vec4 frag_color;\n"
                    "void main() {\n"
                    "  frag_color = color;\n"
                    "}\n"
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