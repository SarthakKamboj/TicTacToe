#pragma once

#include "managers.h"
#include "SDL.h"

struct opengl_object_data {
	int vao_idx;
	int ebo_idx;
	int shader_idx;
	int vbo_idx;
};

struct globals_t {
	ebo_manager_t* ebo_manager = NULL;
	shader_manager_t* shader_manager = NULL;
	vao_manager_t* vao_manager = NULL;
	SDL_Window* window;
	opengl_object_data rectangle_data;
	opengl_object_data outline_circle_data;
};
