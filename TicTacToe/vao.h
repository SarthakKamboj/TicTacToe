#pragma once

#include "glad/glad.h"
#include "vbo.h"

struct vao_t {
	GLuint id = 0;
};

vao_t create_vao();
void bind_vao(const vao_t& vao);
void unbind_vao();
void vao_enable_attribute(vao_t& vao, const vbo_t& vbo, const int attrId, const int numValues, const int dType, const int normalized, const int stride, const int offset);
