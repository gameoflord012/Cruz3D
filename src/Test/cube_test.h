#include "ShaderDesc.h"

#define CRUZ_IMPL
#include <Cruz3D/Cruz3D.h>
#undef CRUZ_IMPL

#include <cstdio>
#include <glm/gtc/matrix_transform.hpp>
#include <assimp/scene.h>


// clang-format off
static float s_vertices[] = {
     1.0, -1.0, -1.0,   1.0, 0.0, 0.0, 1.0,
    -1.0, -1.0, -1.0,   1.0, 0.0, 0.0, 1.0,
    -1.0,  1.0, -1.0,   1.0, 0.0, 0.0, 1.0,
     1.0,  1.0, -1.0,   1.0, 0.0, 0.0, 1.0,

    -1.0, -1.0,  1.0,   0.0, 1.0, 0.0, 1.0,
     1.0, -1.0,  1.0,   0.0, 1.0, 0.0, 1.0,
     1.0,  1.0,  1.0,   0.0, 1.0, 0.0, 1.0,
    -1.0,  1.0,  1.0,   0.0, 1.0, 0.0, 1.0,

    -1.0, -1.0, -1.0,   0.0, 0.0, 1.0, 1.0,
    -1.0,  1.0, -1.0,   0.0, 0.0, 1.0, 1.0,
    -1.0,  1.0,  1.0,   0.0, 0.0, 1.0, 1.0,
    -1.0, -1.0,  1.0,   0.0, 0.0, 1.0, 1.0,

    1.0, -1.0, -1.0,    1.0, 0.5, 0.0, 1.0,
    1.0,  1.0, -1.0,    1.0, 0.5, 0.0, 1.0,
    1.0,  1.0,  1.0,    1.0, 0.5, 0.0, 1.0,
    1.0, -1.0,  1.0,    1.0, 0.5, 0.0, 1.0,

    -1.0, -1.0, -1.0,   0.0, 0.5, 1.0, 1.0,
    -1.0, -1.0,  1.0,   0.0, 0.5, 1.0, 1.0,
     1.0, -1.0,  1.0,   0.0, 0.5, 1.0, 1.0,
     1.0, -1.0, -1.0,   0.0, 0.5, 1.0, 1.0,

    -1.0,  1.0, -1.0,   1.0, 0.0, 0.5, 1.0,
    -1.0,  1.0,  1.0,   1.0, 0.0, 0.5, 1.0,
     1.0,  1.0,  1.0,   1.0, 0.0, 0.5, 1.0,
     1.0,  1.0, -1.0,   1.0, 0.0, 0.5, 1.0
};

static uint16_t s_indices[] = {
    0,  1,  2,   0,  2,  3,
    6,  5,  4,   7,  6,  4,
    8,  9,  10,  8,  10, 11,
    14, 13, 12,  15, 14, 12,
    16, 17, 18,  16, 18, 19,
    22, 21, 20,  23, 22, 20
};

static sg_shader s_shd;
static sg_pipeline s_pip;
static sg_buffer s_vbuf;
static sg_buffer s_ibuf;
static sg_bindings s_bind;
static sg_pass_action s_pass_action;
// clang-format on

// ███████╗██╗░░░██╗███╗░░██╗░█████╗░████████╗██╗░█████╗░███╗░░██╗░██████╗
// ██╔════╝██║░░░██║████╗░██║██╔══██╗╚══██╔══╝██║██╔══██╗████╗░██║██╔════╝
// █████╗░░██║░░░██║██╔██╗██║██║░░╚═╝░░░██║░░░██║██║░░██║██╔██╗██║╚█████╗░
// ██╔══╝░░██║░░░██║██║╚████║██║░░██╗░░░██║░░░██║██║░░██║██║╚████║░╚═══██╗
// ██║░░░░░╚██████╔╝██║░╚███║╚█████╔╝░░░██║░░░██║╚█████╔╝██║░╚███║██████╔╝
// ╚═╝░░░░░░╚═════╝░╚═╝░░╚══╝░╚════╝░░░░╚═╝░░░╚═╝░╚════╝░╚═╝░░╚══╝╚═════╝░

static void sokol_init()
{
    sg_setup({
        .logger = {.func = slog_func},
        .environment = sglue_environment(),
    });

    s_vbuf = sg_make_buffer({.data = SG_RANGE(s_vertices)});
    s_ibuf = sg_make_buffer({.type = SG_BUFFERTYPE_INDEXBUFFER, .data = SG_RANGE(s_indices)});
    s_bind = {.vertex_buffers = {s_vbuf}, .index_buffer = s_ibuf};

    s_shd = sg_make_shader(Cruz::ShaderDecs::BasicMVP);
    s_pip = sg_make_pipeline({
        .shader = s_shd,
        .layout = {.buffers = {{.stride = 28}},
                   .attrs = {{.format = SG_VERTEXFORMAT_FLOAT3}, {.format = SG_VERTEXFORMAT_FLOAT4}}},
        .depth =
            {
                .compare = SG_COMPAREFUNC_LESS_EQUAL,
                .write_enabled = false,
            },
        .index_type = SG_INDEXTYPE_UINT16,
        .cull_mode = SG_CULLMODE_BACK,
    });
}

float s_rx = 0.0f, s_ry = 0.0f;

static void sokol_frame()
{
    glm::mat4x4 proj = glm::perspective(1.0f, sapp_widthf() / sapp_heightf(), 0.01f, 10.0f);
    glm::mat4x4 view = glm::lookAt(glm::vec3{0.0f, 0.0f, 5.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f});
    glm::mat4x4 view_proj = proj * view;

    // rotated model matrix
    s_rx += 1.0f / 60;
    s_ry += 2.0f / 60;

    glm::mat4x4 model{1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};

    model = glm::rotate(model, s_rx, {1.0f, 0.0f, 0.0f});
    model = glm::rotate(model, s_ry, {0.0f, 1.0f, 0.0f});

    // model-view-projection matrix for vertex shader
    Cruz::ShaderDecs::BasicMVP_uniform vs_params = {.mvp = view_proj * model};

    sg_begin_pass({.action = s_pass_action, .swapchain = sglue_swapchain()});
    sg_apply_pipeline(s_pip);
    sg_apply_bindings(s_bind);
    sg_apply_uniforms(SG_SHADERSTAGE_VS, 0, SG_RANGE(vs_params));
    sg_draw(0, 36, 1);
    sg_end_pass();
    sg_commit();
}

static void sokol_cleanup()
{
    sg_shutdown();
}