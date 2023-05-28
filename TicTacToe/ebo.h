#pragma once

#include "glad/glad.h"
#include <array>


/*
class EBO {
public:
	EBO(unsigned int* indicies, int sizeOfBuffer);
	EBO();
	GLuint id;
	int numIndicies;
	void bind();
	void unbind();
	std::array<int, 6> getVertices();
};
*/

struct ebo_t {
	GLuint id = 0;
	int numIndicies = -1;
};

ebo_t create_ebo(const unsigned int* indicies, const int size_of_buffer);
void bind_ebo(const ebo_t& ebo);
void unbind_ebo();
