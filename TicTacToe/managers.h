#pragma once

#include <vector>
#include "ebo.h"
#include "shader.h"
#include "vao.h"
#include "vbo.h"

struct ebo_manager_t {
	std::vector<ebo_t> ebos;
};

struct shader_manager_t {
	std::vector<shader_t> shaders;
};

struct vao_manager_t {
	std::vector<vao_t> vaos;
};

struct vbo_manager_t {
	std::vector<vbo_t> vbos;
};

int add_ebo(ebo_manager_t& manager, ebo_t& ebo);
int add_shader(shader_manager_t& manager, shader_t& shader);
int add_vao(vao_manager_t& manager, vao_t& vao);
int add_vbo(vbo_manager_t& manager, vbo_t& vbo);

