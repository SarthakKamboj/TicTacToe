#include <ft2build.h>
#include FT_FREETYPE_H  

#include "init.h"
#include "globals.h"
#include "SDL.h"
#include "glad/glad.h"
#include <iostream>
#include "constants.h"
#include "vertex.h"
#include "vbo.h"
#include "vao.h"
#include "transform.h"
#include "managers.h"
#include "rectangle.h"
#include "freetype/freetype.h"
#include "font.h"

globals_t globals;

void init_sdl() {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::cout << "SDL could not be initialized: " << SDL_GetError() << std::endl;
		return;
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	globals.window = SDL_CreateWindow("window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

	if (globals.window == NULL) {
		std::cout << "SDL window could not be created: " << SDL_GetError() << std::endl;
		return;
	}

	SDL_GLContext context = SDL_GL_CreateContext(globals.window);
	gladLoadGLLoader(SDL_GL_GetProcAddress);

	SDL_GL_MakeCurrent(globals.window, context);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void init_managers() {
	globals.ebo_manager = new ebo_manager_t;
	globals.shader_manager = new shader_manager_t;
	globals.vao_manager = new vao_manager_t;
	globals.vbo_manager = new vbo_manager_t;
}

void init_rectangle_data() {
	vertex_t vertices[4];
	vertices[0] = create_vertex(glm::vec3(0.5f, 0.5f, 0.0f), glm::vec3(0.f), glm::vec2(0.f));
	vertices[1] = create_vertex(glm::vec3(0.5f, -0.5f, 0.0f), glm::vec3(0.f), glm::vec2(0.f));
	vertices[2] = create_vertex(glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec3(0.f), glm::vec2(0.f));
	vertices[3] = create_vertex(glm::vec3(-0.5f, 0.5f, 0.0f), glm::vec3(0.f), glm::vec2(0.f));

	vbo_t vbo = create_vbo((float*)vertices, sizeof(vertices));

	unsigned int indices[] = {
		0, 1, 3,
		1, 2, 3
	};

	ebo_t ebo = create_ebo(indices, sizeof(indices));
	vao_t vao = create_vao();

	bind_vao(vao);
	vao_enable_attribute(vao, vbo, 0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex_t), offsetof(vertex_t, position));
	bind_ebo(ebo);
	unbind_vao();
	unbind_ebo();

	shader_t shader = create_shader("C:\\Sarthak\\projects\\TicTacToe\\TicTacToe\\shaders\\piece.vert", "C:\\Sarthak\\projects\\TicTacToe\\TicTacToe\\shaders\\piece.frag");

	int ebo_idx = add_ebo(*globals.ebo_manager, ebo);
	int shader_idx = add_shader(*globals.shader_manager, shader);
	int vao_idx = add_vao(*globals.vao_manager, vao);

	opengl_object_data& rec_data = globals.rectangle_data;
	rec_data.ebo_idx = ebo_idx;
	rec_data.shader_idx = shader_idx;
	rec_data.vao_idx = vao_idx;

}

void init_outline_circle_data(int num_points, float inner_radius, float outer_radius) {
	if (num_points < 3) {
		throw std::exception("not enough points");
	}
	if (inner_radius > outer_radius) {
		throw std::exception("inner radius bigger than outer radius");
	}

	float angleIter = 2 * PI / num_points;

	std::vector<vertex_t> vertices;
	std::vector<int> indicies;

	for (int i = 0; i < num_points; i++) {
		vertex_t bottomLeft, bottomRight, topLeft, topRight;

		float angle = angleIter * i;
		bottomLeft.position = glm::vec3(inner_radius * cosf(angle + angleIter), inner_radius * sinf(angle + angleIter), 0.0f);
		bottomRight.position = glm::vec3(inner_radius * cosf(angle), inner_radius * sinf(angle), 0.0f);
		topLeft.position = glm::vec3(outer_radius * cosf(angle + angleIter), outer_radius * sinf(angle + angleIter), 0.0f);
		topRight.position = glm::vec3(outer_radius * cosf(angle), outer_radius * sinf(angle), 0.0f);

		int curLen = vertices.size();

		vertices.push_back(bottomLeft);
		vertices.push_back(bottomRight);
		vertices.push_back(topLeft);
		vertices.push_back(topRight);

		int bottomLeftIdx = curLen;
		int bottomRightIdx = curLen + 1;
		int topLeftIdx = curLen + 2;
		int topRightIdx = curLen + 3;

		indicies.push_back(bottomLeftIdx);
		indicies.push_back(topLeftIdx);
		indicies.push_back(topRightIdx);
		indicies.push_back(topRightIdx);
		indicies.push_back(bottomRightIdx);
		indicies.push_back(bottomLeftIdx);
	}

	vbo_t vbo = create_vbo((float*)vertices.data(), vertices.size() * sizeof(vertices[0]));
	ebo_t ebo = create_ebo((unsigned int*)indicies.data(), indicies.size() * sizeof(indicies[0]));
	vao_t vao = create_vao();

	bind_vao(vao);
	vao_enable_attribute(vao, vbo, 0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex_t), offsetof(vertex_t, position));
	vao_enable_attribute(vao, vbo, 1, 3, GL_FLOAT, GL_FALSE, sizeof(vertex_t), offsetof(vertex_t, color));
	vao_enable_attribute(vao, vbo, 2, 2, GL_FLOAT, GL_FALSE, sizeof(vertex_t), offsetof(vertex_t, tex_coord));

	bind_ebo(ebo);
	unbind_vao();
	unbind_ebo();

	shader_t shader = create_shader("C:\\Sarthak\\projects\\TicTacToe\\TicTacToe\\shaders\\piece.vert", "C:\\Sarthak\\projects\\TicTacToe\\TicTacToe\\shaders\\piece.frag");
	shader_set_vec3(shader, "color", glm::vec3(0, 1, 0));

	int ebo_idx = add_ebo(*globals.ebo_manager, ebo);
	int shader_idx = add_shader(*globals.shader_manager, shader);
	int vao_idx = add_vao(*globals.vao_manager, vao);

	opengl_object_data& rec_data = globals.outline_circle_data;
	rec_data.ebo_idx = ebo_idx;
	rec_data.shader_idx = shader_idx;
	rec_data.vao_idx = vao_idx;
}

void setup_board_objects(std::vector<rectangle_t>& rectangles) {
	float offset = 0.25f;
	float shorter_scale = 0.035f;
	glm::vec3 wall_color = glm::vec3(13, 161, 146) / 255.f;

	rectangle_t left_wall = create_rectangle(glm::vec3(-offset, 0.0f, 0.0f), glm::vec3(shorter_scale, 1.5f, 0.0f), 0.0f, wall_color);
	rectangle_t right_wall = create_rectangle(glm::vec3(offset, 0.0f, 0.0f), glm::vec3(shorter_scale, 1.5f, 0.0f), 0.0f, wall_color);
	rectangle_t top_wall = create_rectangle(glm::vec3(0.f, offset, 0.0f), glm::vec3(shorter_scale, 1.5f, 0.0f), 90.0f, wall_color);
	rectangle_t bottom_wall = create_rectangle(glm::vec3(0.0f, -offset, 0.0f), glm::vec3(shorter_scale, 1.5f, 0.0f), 90.0f, wall_color);

	rectangles.push_back(left_wall);
	rectangles.push_back(right_wall);
	rectangles.push_back(top_wall);
	rectangles.push_back(bottom_wall);
}

void init_fonts() {
	if (FT_Init_FreeType(&globals.ft_library))
	{
		std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
		return;
	}

	globals.font = create_font("C:\\Sarthak\\projects\\TicTacToe\\TicTacToe\\ext\\fonts\\Lilita_One\\LilitaOne-Regular.ttf");
}

void init_text_quad() {
	vertex_t vertices[4];
	vertices[0] = create_vertex(glm::vec3(0.f), glm::vec3(0.f), glm::vec2(1.0f, 1.0f)); // top right
	vertices[1] = create_vertex(glm::vec3(0.f), glm::vec3(0.f), glm::vec2(1.f, 0.0f)); // bottom right
	vertices[2] = create_vertex(glm::vec3(0.f), glm::vec3(0.f), glm::vec2(0.0f, 0.f)); // bottom left
	vertices[3] = create_vertex(glm::vec3(0.f), glm::vec3(0.f), glm::vec2(0.0f, 1.f)); // top left

	vbo_t vbo = create_vbo((float*)vertices, sizeof(vertices));

	unsigned int indices[] = {
		0, 1, 3,
		1, 2, 3
	};

	ebo_t ebo = create_ebo(indices, sizeof(indices), GL_DYNAMIC_DRAW);
	vao_t vao = create_vao();

	bind_vao(vao);
	vao_enable_attribute(vao, vbo, 0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex_t), offsetof(vertex_t, position));
	vao_enable_attribute(vao, vbo, 1, 2, GL_FLOAT, GL_FALSE, sizeof(vertex_t), offsetof(vertex_t, tex_coord));
	bind_ebo(ebo);
	unbind_vao();
	unbind_ebo();

	shader_t shader = create_shader("C:\\Sarthak\\projects\\TicTacToe\\TicTacToe\\shaders\\text.vert", "C:\\Sarthak\\projects\\TicTacToe\\TicTacToe\\shaders\\text.frag");
	glm::mat4 projection = glm::ortho(0.0f, (float)SCREEN_WIDTH, 0.0f, (float)SCREEN_HEIGHT);
	shader_set_mat4(shader, "projection", projection);
	shader_set_int(shader, "char_texture", 0);

	int ebo_idx = add_ebo(*globals.ebo_manager, ebo);
	int shader_idx = add_shader(*globals.shader_manager, shader);
	int vao_idx = add_vao(*globals.vao_manager, vao);
	int vbo_idx = add_vbo(*globals.vbo_manager, vbo);

	opengl_object_data& quad_data = globals.text_quad_data;
	quad_data.ebo_idx = ebo_idx;
	quad_data.shader_idx = shader_idx;
	quad_data.vao_idx = vao_idx;
	quad_data.vbo_idx = vbo_idx;
}

void init() {
	init_sdl();
	init_managers();
	init_rectangle_data();
	init_outline_circle_data(64, 0.15f, 0.2f);
	init_fonts();
	init_text_quad();
	globals.game_state = new game_state_t;
}