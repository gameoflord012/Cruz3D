#pragma once

#define CRUZ_IMPL
#include <Cruz3D/Cruz3D.h>
#undef CRUZ_IMPL

#include <Cruz3D/Debug.h>
#include <Cruz3D/Graphic.h>
#include <Cruz3D/Graphic/Passes.h>
#include <Cruz3D/Input.h>
#include <Cruz3D/Settings.h>

#include <glm/gtc/matrix_transform.hpp>

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include <cstdio>
#include <memory>

static cruz::unique_ptrs<cruz::Mesh> s_meshes; // array of meshes
static cruz::unique_ptrs<cruz::Material> s_mats;

static cruz::Scene *s_scene;
static cruz::SimplePass *s_pass;
static cruz::SimpleBinding *s_binding;

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

    s_pass = new cruz::SimplePass();
    s_binding = new cruz::SimpleBinding(*s_meshes[2], *s_mats[1]);
}

static void UpdateCameraMovement()
{
    int mX{}, mY{}, mZ{};
    if (INPUT_INS.IsKeyDown(SAPP_KEYCODE_W))
        mZ++;
    if (INPUT_INS.IsKeyDown(SAPP_KEYCODE_S))
        mZ--;
    if (INPUT_INS.IsKeyDown(SAPP_KEYCODE_D))
        mX++;
    if (INPUT_INS.IsKeyDown(SAPP_KEYCODE_A))
        mX--;

    if (INPUT_INS.IsKeyDown(SAPP_KEYCODE_SPACE))
    {
        if ((INPUT_INS.GetModifiers() & SAPP_MODIFIER_SHIFT))
            mY--;
        else
            mY++;
    }

    float delta = (float)sapp_frame_duration();
    s_cam->MoveRel(glm::vec3(mX, mY, mZ) * delta * cruz::settings::CAMERA_MOVESPEED);

    if (INPUT_INS.IsMouseMoving() && INPUT_INS.IsMouseDown(SAPP_MOUSEBUTTON_MIDDLE))
    {
        s_cam->Rotate(glm::vec3(INPUT_INS.GetMouseDelta().y, INPUT_INS.GetMouseDelta().x, 0.0f) * delta *
                      cruz::settings::MOUSE_SENSITIVITY);
    }
}

static void sokol_init()
{
    sg_setup({
        .logger = {.func = slog_func},
        .environment = sglue_environment(),
    });

    InitData();
}

static void sokol_event(const sapp_event *event)
{
    INPUT_INS.ProcessEvent(event);
}

static void sokol_frame()
{
    INPUT_INS.Frame();

    static float s_rx{};
    static float s_ry{};

    UpdateCameraMovement();

    // rotated model matrix
    // s_rx += 1.0f / 60;
    // s_ry += 2.0f / 60;

    glm::mat4x4 model{1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};

    model = glm::rotate(model, s_rx, {1.0f, 0.0f, 0.0f});
    model = glm::rotate(model, s_ry, {0.0f, 1.0f, 0.0f});

    s_pass->Begin();
    {
        s_pass->ApplyBinding(s_binding);
        s_pass->ApplyVSUniform({.mvp = s_cam->GetProjView() * model});
        s_pass->Draw();
    }
    s_pass->End();
}

static void sokol_cleanup()
{
    sg_shutdown();
}
