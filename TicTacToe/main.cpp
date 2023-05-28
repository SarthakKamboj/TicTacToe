#include <iostream>
#include "SDL.h"
#include "texture.h"
#include "glad/glad.h"
#include "shader.h"
#include "vao.h"
#include "vbo.h"
#include "vertex.h"
#include "ebo.h"
#include "transform.h"
#include "rectangle.h"
#include "cross.h"
#include <vector>
#include <array>
#include <cmath>
#include "circle.h"
#include "helper.h"
#include "globals.h"
#include "constants.h"
#include "enums.h"
#include "init.h"
#include "input.h"

extern globals_t globals;

int main(int argc, char** argv) {
	
	int state[3][3]{};		
	init();

	std::vector<rectangle_t> rectangles;
	setup_board_objects(rectangles);

	texture_t texture = create_texture("C:\\Sarthak\\projects\\TicTacToe\\TicTacToe\\smiley_face.jpg");

	PLAYER player = PLAYER::ONE;

	bool running = true;
	bool game_over = false;

	cross_t temp_cross = create_cross(glm::vec3(0), glm::vec3(1.f), glm::vec3(1, 0, 0));
	ouline_circle_t temp_circle = create_outline_circle(glm::vec3(0), glm::vec3(1.f), 0.f, glm::vec3(1, 0, 0));

	std::vector<cross_t> placed_crosses;
	std::vector<ouline_circle_t> placed_circles;

	rectangle_t finish_line;
	mouse_state_t mouse_state;
	key_state_t key_state;

	while (running) {
		memset(&mouse_state, 0, sizeof(mouse_state_t));
		memset(&key_state, 0, sizeof(key_state_t));

		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			handle_input(event, mouse_state, key_state);
			if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(globals.window)) {
				running = false;
			}
			switch (event.type) {
			case SDL_QUIT: {
				running = false;
			}
						 break;
			}
		}

		std::cout << mouse_state.x << " " << mouse_state.y << std::endl;

		glm::vec3 bck_color = glm::vec3(20, 189, 172) / 255.f;
		glClearColor(bck_color.x, bck_color.y, bck_color.z, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		bind_texture(texture);

		for (const rectangle_t& rectangle : rectangles) {
			draw_rectangle(rectangle);
		}

		glm::vec2 ndc = helper::screen_to_ndc(glm::vec2(mouse_state.x, mouse_state.y));
		float offset = 0.25f;
		glm::vec2 mouse_over_idx = helper::get_ttt_box_idx_from_ndc(ndc, offset);

		if (player == PLAYER::ONE) {
			temp_cross.transform.position = helper::get_ttt_box_ndc_from_idx(mouse_over_idx);
			draw_cross(temp_cross);
		}
		else {
			temp_circle.transform.position = helper::get_ttt_box_ndc_from_idx(mouse_over_idx);
			draw_outline_circle(temp_circle);
		}

		if (mouse_state.mouse_up) {
			if (player == ONE) {
				placed_crosses.push_back(temp_cross);
				cross_t& new_cross = placed_crosses[placed_crosses.size() - 1];
				new_cross.color = glm::vec3(0.37f);
				player = TWO;
				state[(int)mouse_over_idx.y][(int)mouse_over_idx.x] = ONE;
			}
			else {
				placed_circles.push_back(temp_circle);
				ouline_circle_t& new_circle = placed_circles[placed_circles.size() - 1];
				new_circle.color = glm::vec3(1, 1, 1);
				player = ONE;
				state[(int)mouse_over_idx.y][(int)mouse_over_idx.x] = TWO;
			}
		}

		for (const cross_t& cross : placed_crosses) {
			draw_cross(cross);
		}

		for (const ouline_circle_t& circle : placed_circles) {
			draw_outline_circle(circle);
		}

		finish_state_t finish_state = helper::is_game_over(state);
		if (!game_over && finish_state.winner != 0) {
			glm::vec3 start_pos = helper::get_ttt_box_ndc_from_idx(finish_state.start_ttt_idx);
			glm::vec3 end_pos = helper::get_ttt_box_ndc_from_idx(finish_state.end_ttt_idx);
			float distance = glm::length(end_pos - start_pos);

			glm::vec3 pos = (start_pos + end_pos) / 2.0f;
			glm::vec3 scale(distance * 1.15f, 0.035f, 1.f);
			glm::vec3 rel_pos = end_pos - start_pos;
			float dX = helper::dot_product(rel_pos, glm::vec3(1.0f, 0.f, 0.f));
			float dY = helper::dot_product(rel_pos, glm::vec3(0.0f, 1.f, 0.f));
			float rotation = (dY >= 0.f ? 1.f : -1.f) * glm::degrees(acosf(dX));
			finish_line = create_rectangle(pos, scale, rotation, glm::vec3(0.8f));
			game_over = true;
		}

		if (game_over) {
			draw_rectangle(finish_line);
		}

		SDL_GL_SwapWindow(globals.window);
	}

	return -1;
}