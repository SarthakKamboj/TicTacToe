#pragma once

#include "glad/glad.h"
#include <array>

struct ebo_t {
	GLuint id = 0;
	int numIndicies = -1;
};

ebo_t create_ebo(const unsigned int* indicies, const int size_of_buffer);
void bind_ebo(const ebo_t& ebo);
void unbind_ebo();
void delete_ebo(const ebo_t& ebo);
