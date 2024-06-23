#pragma once

#define CRUZ_IMPL
#include <Cruz3D/Cruz3D.h>
#undef CRUZ_IMPL

#include <Cruz3D/Graphic.h>

#include <cstdio>
#include <debugapi.h>

#include <glm/gtc/matrix_transform.hpp>

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

constexpr unsigned int AI_PROCESS_FLAGS = aiProcess_Triangulate | aiProcess_JoinIdenticalVertices;

static sg_shader s_shd;
static cruz::Mesh s_mesh;
static cruz::Pipeline* s_pip;
static sg_bindings s_bind;
static sg_pass_action s_pass_action;
static const aiScene* s_scene;

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
	s_scene = importer.ReadFile(CRUZ_DATA_DIR "/metal_trash_can_4k.obj", AI_PROCESS_FLAGS);

	if (!s_scene)
	{
		OutputDebugStringA(importer.GetErrorString());
		assert(false);
	}

	for (unsigned int i = 0; i < s_scene->mNumMeshes; i++)
	{
		s_mesh.AddMesh(*s_scene->mMeshes[i]);
	}

	const sg_buffer vbuf = cruz::make_vertex_buffer(s_mesh.GetVBuf());
	const sg_buffer ibuf = cruz::make_index_buffer(s_mesh.GetIBuf());

	s_bind = { .vertex_buffers = {vbuf}, .index_buffer = ibuf };
	s_pip =  new cruz::Pipeline(cruz::make_shader("BasicMVP"));
}

static float s_rx;
static float s_ry; 

static void sokol_frame()
{ 
	const glm::mat4x4 proj = glm::perspective(1.0f, sapp_widthf() / sapp_heightf(), 0.01f, 10.0f);
	const glm::mat4x4 view = glm::lookAt(glm::vec3{ 0.0f, 0.0f, 2.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f });
	const glm::mat4x4 view_proj = proj * view;

	// rotated model matrix 
	s_rx += 1.0f / 60;
	s_ry += 2.0f / 60;

	glm::mat4x4 model{ 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };

	model = glm::rotate(model, s_rx, { 1.0f, 0.0f, 0.0f });
	model = glm::rotate(model, s_ry, { 0.0f, 1.0f, 0.0f });

	// model-view-projection matrix for vertex shader
	const cruz::ShaderDesc::BasicMVP_uniform vs_params = { .mvp = view_proj * model };

	sg_begin_pass({ .action = s_pass_action, .swapchain = sglue_swapchain() });
	sg_apply_pipeline(s_pip->sg_pip());
	sg_apply_bindings(s_bind);
	sg_apply_uniforms(SG_SHADERSTAGE_VS, 0, SG_RANGE(vs_params));
	sg_draw(0, s_mesh.NumberOfIndicies(), 1);
	sg_end_pass();
	sg_commit();
}

static void sokol_cleanup()
{
	sg_shutdown();
}
