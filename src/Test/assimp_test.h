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

const unsigned int AI_PROCESS_FLAGS = aiProcess_Triangulate | aiProcess_JoinIdenticalVertices;

static cruz::VertexBuffer s_vertices;
static cruz::IndexBuffer s_indices;

static sg_shader s_shd;
static cruz::Pipeline* s_pip;
static sg_buffer s_vbuf;
static sg_buffer s_ibuf;
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
	s_scene = importer.ReadFile(CRUZ_DATA_DIR "/monkey.obj", AI_PROCESS_FLAGS);

	if (!s_scene)
	{
		OutputDebugStringA(importer.GetErrorString());
		assert(false);
	}

	for (unsigned int i = 0; i < s_scene->mNumMeshes; i++)
	{
		for (unsigned int j = 0; j < s_scene->mMeshes[i]->mNumVertices; j++)
		{
			const aiVector3D& vertex = s_scene->mMeshes[i]->mVertices[j];
			s_vertices.Push(vertex);
			s_vertices.Push({ 1, 0, 0, 1 });
		}

		for (size_t j = 0; j < s_scene->mMeshes[i]->mNumFaces; j++)
		{
			const aiFace& face = s_scene->mMeshes[i]->mFaces[j];
			s_indices.Push(face);
		}
	}

	s_vbuf = cruz::make_vertex_buffer(s_vertices);
	s_ibuf = cruz::make_index_buffer(s_indices);
	s_bind = { .vertex_buffers = {s_vbuf}, .index_buffer = s_ibuf };

	s_pip = new cruz::Pipeline(cruz::make_shader("BasicMVP"));
}

static float s_rx;
static float s_ry;

static void sokol_frame()
{
	glm::mat4x4 proj = glm::perspective(1.0f, sapp_widthf() / sapp_heightf(), 0.01f, 10.0f);
	glm::mat4x4 view = glm::lookAt(glm::vec3{ 0.0f, 0.0f, 2.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f });
	glm::mat4x4 view_proj = proj * view;

	// rotated model matrix
	s_rx += 1.0f / 60;
	s_ry += 2.0f / 60;

	glm::mat4x4 model{ 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };

	model = glm::rotate(model, s_rx, { 1.0f, 0.0f, 0.0f });
	model = glm::rotate(model, s_ry, { 0.0f, 1.0f, 0.0f });

	// model-view-projection matrix for vertex shader
	cruz::ShaderDesc::BasicMVP_uniform vs_params = { .mvp = view_proj * model };

	sg_begin_pass({ .action = s_pass_action, .swapchain = sglue_swapchain() });
	sg_apply_pipeline(s_pip->sg_pip());
	sg_apply_bindings(s_bind);
	sg_apply_uniforms(SG_SHADERSTAGE_VS, 0, SG_RANGE(vs_params));
	sg_draw(0, (int)s_indices.count(), 1);
	sg_end_pass();
	sg_commit();
}

static void sokol_cleanup()
{
	sg_shutdown();
}
