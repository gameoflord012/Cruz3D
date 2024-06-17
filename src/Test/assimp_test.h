#pragma once

#include "ShaderDesc.h"

#define CRUZ3D_IMPL
#include <Cruz3D/Cruz3D.h>
#undef CRUZ3D_IMPL

#include <debugapi.h>

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <cstdio>

const uint16_t s_buffer_size = 16384;
const unsigned int AI_PROCESS_FLAGS = aiProcess_Triangulate | aiProcess_JoinIdenticalVertices;
static float s_vertices[s_buffer_size];
static unsigned int s_indices[s_buffer_size];
static unsigned int s_num_indices;

static sg_shader s_shd;
static sg_pipeline s_pip;
static sg_buffer s_vbuf;
static sg_buffer s_ibuf;
static sg_bindings s_bind;
static sg_pass_action s_pass_action;
static const aiScene *s_scene;

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

    Assimp::Importer importer;
    s_scene = importer.ReadFile("data/monkey.obj", AI_PROCESS_FLAGS);

    if (!s_scene)
    {
        OutputDebugStringA(importer.GetErrorString());
        assert(false);
    }

    unsigned int numVerticies = 0;
    unsigned int numFaces = 0;
    for (unsigned int i = 0; i < s_scene->mNumMeshes; i++)
    {
        for (unsigned int j = 0; j < s_scene->mMeshes[i]->mNumVertices; j++)
        {
            const aiVector3D &vertex = s_scene->mMeshes[i]->mVertices[j];

            // clang-format off
            s_vertices[numVerticies * 7    ] = vertex.x;
            s_vertices[numVerticies * 7 + 1] = vertex.y;
            s_vertices[numVerticies * 7 + 2] = vertex.z;

            s_vertices[numVerticies * 7 + 3] = 1;
            s_vertices[numVerticies * 7 + 4] = 0;
            s_vertices[numVerticies * 7 + 5] = 0;
            s_vertices[numVerticies * 7 + 6] = 1;
            // clang-format on

            numVerticies++;
        }

        for (size_t j = 0; j < s_scene->mMeshes[i]->mNumFaces; j++)
        {
            const aiFace &face = s_scene->mMeshes[i]->mFaces[j];
            assert(face.mNumIndices == 3);

            // clang-format off
            s_indices[numFaces * 3    ] = face.mIndices[0];
            s_indices[numFaces * 3 + 1] = face.mIndices[1];
            s_indices[numFaces * 3 + 2] = face.mIndices[2];
            // clang-format on

            numFaces++;
        }

        s_num_indices = numFaces * 3;
    }

    s_vbuf = sg_make_buffer({.data = SG_RANGE(s_vertices) });
    s_ibuf = sg_make_buffer({.type = SG_BUFFERTYPE_INDEXBUFFER, .data = SG_RANGE(s_indices) });
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
        .index_type = SG_INDEXTYPE_UINT32,
        .cull_mode = SG_CULLMODE_BACK,
    });
}

static float s_rx;
static float s_ry;

static void sokol_frame()
{
    glm::mat4x4 proj = glm::perspective(1.0f, sapp_widthf() / sapp_heightf(), 0.01f, 10.0f);
    glm::mat4x4 view = glm::lookAt(glm::vec3{0.0f, 0.0f, 2.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f});
    glm::mat4x4 view_proj = proj * view;

    // rotated model matrix
    s_rx += 1.0f / 60;
    s_ry += 2.0f / 60;

    glm::mat4x4 model{1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};

    model = glm::rotate(model, s_rx, {1.0f, 0.0f, 0.0f});
    model = glm::rotate(model, s_ry, {0.0f, 1.0f, 0.0f});

    // model-view-projection matrix for vertex shader
    Cruz::ShaderDecs::BasicMVP_params_t vs_params = {.mvp = view_proj * model};

    sg_begin_pass({.action = s_pass_action, .swapchain = sglue_swapchain()});
    sg_apply_pipeline(s_pip);
    sg_apply_bindings(s_bind);
    sg_apply_uniforms(SG_SHADERSTAGE_VS, 0, SG_RANGE(vs_params));
    sg_draw(0, s_num_indices, 1);
    sg_end_pass();
    sg_commit();
}

static void sokol_cleanup()
{
    sg_shutdown();
}
