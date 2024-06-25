#pragma once

#define CRUZ_IMPL
#include <Cruz3D/Cruz3D.h>
#undef CRUZ_IMPL

#include <Cruz3D/Debug.h>
#include <Cruz3D/Graphic.h>
#include <Cruz3D/Input.h>

#include <glm/gtc/matrix_transform.hpp>

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include <cstdio>
#include <memory>

static cruz::unique_ptrs<cruz::Mesh> s_meshes; // array of meshes
static cruz::unique_ptrs<cruz::Material> s_mats;

static cruz::Scene *s_scene;
static sg_bindings s_bind;
static cruz::Pipeline *s_pip;

static cruz::Camera *s_cam;

// ███████╗██╗░░░██╗███╗░░██╗░█████╗░████████╗██╗░█████╗░███╗░░██╗░██████╗
// ██╔════╝██║░░░██║████╗░██║██╔══██╗╚══██╔══╝██║██╔══██╗████╗░██║██╔════╝
// █████╗░░██║░░░██║██╔██╗██║██║░░╚═╝░░░██║░░░██║██║░░██║██╔██╗██║╚█████╗░
// ██╔══╝░░██║░░░██║██║╚████║██║░░██╗░░░██║░░░██║██║░░██║██║╚████║░╚═══██╗
// ██║░░░░░╚██████╔╝██║░╚███║╚█████╔╝░░░██║░░░██║╚█████╔╝██║░╚███║██████╔╝
// ╚═╝░░░░░░╚═════╝░╚═╝░░╚══╝░╚════╝░░░░╚═╝░░░╚═╝░╚════╝░╚═╝░░╚══╝╚═════╝░

static void InitData()
{
    s_cam = new cruz::Camera(sapp_widthf() / sapp_heightf());
    s_scene = new cruz::Scene(CRUZ_DATA_DIR "/metal_trash_can_4k.obj");
    s_meshes = s_scene->GetMeshes();
    s_mats = s_scene->GetMaterials();
}

static void UpdateCameraMovement()
{
    int mZ{}, mX{};
    if (INPUT_INS.IsKeyDown(SAPP_KEYCODE_W))
        mZ++;
    if (INPUT_INS.IsKeyDown(SAPP_KEYCODE_S))
        mZ--;
    if (INPUT_INS.IsKeyDown(SAPP_KEYCODE_D))
        mX++;
    if (INPUT_INS.IsKeyDown(SAPP_KEYCODE_A))
        mX--;

    float delta = (float)sapp_frame_duration();
    s_cam->MoveRel(glm::vec3(mX, 0.0f, mZ) * delta);

    if (INPUT_INS.IsMouseMoving() && INPUT_INS.IsMouseDown(SAPP_MOUSEBUTTON_MIDDLE))
    {
        s_cam->Rotate({INPUT_INS.GetMouseDelta().y * delta, INPUT_INS.GetMouseDelta().x * delta, 0.0f});
    }
}

static void sokol_init()
{
    sg_setup({
        .logger = {.func = slog_func},
        .environment = sglue_environment(),
    });

    InitData();

    sg_image img = sg_make_image(s_mats[1]->GetDiffuse());

    // create a sampler object
    sg_sampler smp = sg_make_sampler({
        .min_filter = SG_FILTER_LINEAR,
        .mag_filter = SG_FILTER_LINEAR,
    });

    const sg_buffer vbuf = cruz::make_vertex_buffer(s_meshes[2]->GetVBuf());
    const sg_buffer ibuf = cruz::make_index_buffer(s_meshes[2]->GetIBuf());

    // clang-format off
    s_bind = {
        .vertex_buffers = { vbuf },
        .index_buffer = ibuf,
        .fs = 
        {
            .images = { img },
            .samplers = { smp },
        }
    };
    // clang-format on

    s_pip = new cruz::Pipeline(cruz::make_shader("BasicMVP"));
}

static void sokol_event(const sapp_event *event)
{
    cruz::singleton::Input.ProcessEvent(event);
}

static void sokol_frame()
{
    static float s_rx{};
    static float s_ry{};

    UpdateCameraMovement();

    // rotated model matrix
    s_rx += 1.0f / 60;
    s_ry += 2.0f / 60;

    glm::mat4x4 model{1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};

    model = glm::rotate(model, s_rx, {1.0f, 0.0f, 0.0f});
    model = glm::rotate(model, s_ry, {0.0f, 1.0f, 0.0f});

    // model-view-projection matrix for vertex shader
    const cruz::ShaderDesc::BasicMVP_uniform vs_params = {.mvp = s_cam->GetProjView() * model};

    sg_begin_pass({.swapchain = sglue_swapchain()});
    sg_apply_pipeline(s_pip->sg_pip());
    sg_apply_bindings(s_bind);
    sg_apply_uniforms(SG_SHADERSTAGE_VS, 0, SG_RANGE(vs_params));
    sg_draw(0, s_meshes[2]->NumberOfIndicies(), 1);
    sg_end_pass();

    sg_commit();
}

static void sokol_cleanup()
{
    sg_shutdown();
}
