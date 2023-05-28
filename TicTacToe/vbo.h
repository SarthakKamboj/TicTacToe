#pragma once

#include "glad/glad.h"

struct vbo_t {
	GLuint id = 0;
};

vbo_t create_vbo(const float* vertices, const int data_size);
void bind_vbo(const vbo_t& vbo);
void unbind_vbo();
