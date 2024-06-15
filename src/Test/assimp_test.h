#pragma once

#define CRUZ3D_IMPL
#include <Cruz3D/Cruz3D.h>
#undef CRUZ3D_IMPL

#include <cstdio>
#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

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
    const aiScene* scene = importer.ReadFile("data/monkey.obj", aiProcess_Triangulate);
}

static void sokol_frame()
{

}

static void sokol_cleanup()
{
    sg_shutdown();
}
