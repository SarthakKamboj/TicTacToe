#pragma once

#include "glad/glad.h"

struct texture_t {
	GLuint id;
};

texture_t create_texture(const char* path);
void bind_texture(const texture_t& texture);
void unbind_texture();
