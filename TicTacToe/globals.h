#pragma once

#include "managers.h"
#include "SDL.h"
#include "game_state.h"
#include "freetype/freetype.h"

struct opengl_object_data {
	int vao_idx = -1;
	int ebo_idx = -1;
	int shader_idx = -1;
	int vbo_idx = -1;
};

struct globals_t {
	ebo_manager_t* ebo_manager = NULL;
	shader_manager_t* shader_manager = NULL;
	vao_manager_t* vao_manager = NULL;
	game_state_t* game_state = NULL;
	SDL_Window* window = NULL;
	opengl_object_data rectangle_data;
	opengl_object_data outline_circle_data;
	FT_Library ft_library;
};
