#pragma once

#include "glad/glad.h"

struct vbo_t {
	GLuint id = 0;
};

vbo_t create_vbo(const float* vertices, const int data_size);
void bind_vbo(const vbo_t& vbo);
void update_vbo_data(const vbo_t& vbo, const float* vertices, const int data_size);
void unbind_vbo();
void delete_vbo(const vbo_t& vbo);
