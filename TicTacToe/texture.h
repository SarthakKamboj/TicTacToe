#pragma once

#include "glad/glad.h"

class Texture {
public:
	Texture(const char* path);
	GLuint id;

	void bind();
	void unbind();

	int width, height;
};
