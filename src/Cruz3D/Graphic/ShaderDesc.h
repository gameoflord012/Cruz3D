#pragma once

#include <glm/gtc/matrix_transform.hpp>
#include <sokol_gfx.h>

namespace cruz
{
namespace ShaderDesc
{
struct BasicMVP_uniform
{
    glm::mat4x4 mvp;
};

static const sg_shader_desc BasicMVP{
    .vs = {.source = "#version 330\n"
                     "uniform mat4 mvp;\n"
                     "layout(location=0) in vec4 position;\n"
                     "layout(location=1) in vec4 color0;\n"
                     "out vec4 color;\n"
                     "void main() {\n"
                     "  gl_Position = mvp * position;\n"
                     "  color = color0;\n"
                     "}\n",

           .uniform_blocks = {{.size = sizeof(BasicMVP_uniform),
                               .uniforms = {{.name = "mvp", .type = SG_UNIFORMTYPE_MAT4}}}}},
    /* NOTE: since the shader defines explicit attribute locations,
        we don't need to provide an attribute name lookup table in the shader
    */
    .fs = {.source = "#version 330\n"
                     "in vec4 color;\n"
                     "out vec4 frag_color;\n"
                     "void main() {\n"
                     "  frag_color = color;\n"
                     "}\n"}};
} // namespace ShaderDesc
} // namespace cruz