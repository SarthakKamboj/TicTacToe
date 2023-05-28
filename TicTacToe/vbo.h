#pragma once

#include "glad/glad.h"

/*
class VBO {
public:
	VBO(float* vertices, int dataSize);
	VBO();
	GLuint id;
	void bind();
	void unbind();
};
*/

struct vbo_t {
	GLuint id = 0;
};

vbo_t create_vbo(const float* vertices, const int data_size);
void bind_vbo(const vbo_t& vbo);
void unbind_vbo();
