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
#include "font.h"
#include "button.h" 

extern globals_t globals;

int main(int argc, char** argv) {

	init();

	std::vector<rectangle_t> rectangles;
	setup_board_objects(rectangles);

	texture_t texture = create_texture("C:\\Sarthak\\projects\\TicTacToe\\TicTacToe\\smiley_face.jpg");

	bool running = true;

	glm::vec3 temp_color(1, 1, 0);
	glm::vec3 temp_error_color(1, 0, 0);
	cross_t temp_cross = create_cross(glm::vec3(0), glm::vec3(1.f), temp_color);
	ouline_circle_t temp_circle = create_outline_circle(glm::vec3(0), glm::vec3(1.f), 0.f, temp_color);

	std::vector<cross_t> placed_crosses;
	std::vector<ouline_circle_t> placed_circles;

	rectangle_t finish_line;
	mouse_state_t mouse_state;
	key_state_t key_state;
	finish_state_t finish_state;
	glm::vec3 text_color = glm::vec3(0.75f);

	button_t play_btn = create_button("play", text_color, WALL_COLOR * 1.1f, WALL_COLOR, glm::vec3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.f), glm::vec3(1), glm::vec3(15.f, 5.f, 0.f));
	button_t quit_btn = create_button("quit", text_color, WALL_COLOR * 1.1f, WALL_COLOR, glm::vec3(SCREEN_WIDTH / 2, (SCREEN_HEIGHT / 2) - 100.f, 0.f), glm::vec3(1), glm::vec3(15.f, 5.f, 0.f));

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
		SDL_GetMouseState(&mouse_state.x, &mouse_state.y);

		glm::vec3 bck_color = glm::vec3(20, 189, 172) / 255.f;
		glClearColor(bck_color.x, bck_color.y, bck_color.z, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		if (globals.scene == SCENE::TITLE) {
			std::string title_text = GAME_TITLE;
			glm::vec3 title_scale(2.f);
			float title_text_width = get_text_width(globals.font, title_text, title_scale.x);
			float title_text_height = get_text_height(globals.font, title_text, title_scale.y);

			update_button(play_btn, mouse_state);
			update_button(quit_btn, mouse_state);

			if (play_btn.pressed_on) {
				globals.scene = SCENE::GAME;
			}

			if (quit_btn.pressed_on) {
				running = false;
				continue;
			}

			draw_text(globals.font, title_text, (SCREEN_WIDTH - title_text_width) / 2.f, SCREEN_HEIGHT - title_text_height - 100.f, title_scale, text_color);
			draw_button(play_btn);
			draw_button(quit_btn);
		}
		else if (globals.scene == SCENE::GAME) {
			glm::vec2 ndc = helper::mouse_to_ndc(glm::vec2(mouse_state.x, mouse_state.y));
			float offset = 0.25f;
			glm::vec2 mouse_over_idx = helper::get_ttt_box_idx_from_ndc(ndc, offset);

			game_state_t& game_state = *globals.game_state;
			auto& state = game_state.state;

			if (mouse_state.mouse_up && state[(int)mouse_over_idx.y][(int)mouse_over_idx.x] == 0 && !game_state.game_over && game_state.num_moves < 9) {
				game_state.num_moves++;
				if (game_state.cur_player == ONE) {
					placed_crosses.push_back(temp_cross);
					cross_t& new_cross = placed_crosses[placed_crosses.size() - 1];
					new_cross.color = glm::vec3(0.37f);
					game_state.cur_player = TWO;
					state[(int)mouse_over_idx.y][(int)mouse_over_idx.x] = ONE;
				}
				else {
					placed_circles.push_back(temp_circle);
					ouline_circle_t& new_circle = placed_circles[placed_circles.size() - 1];
					new_circle.color = glm::vec3(1, 1, 1);
					game_state.cur_player = ONE;
					state[(int)mouse_over_idx.y][(int)mouse_over_idx.x] = TWO;
				}

				finish_state = helper::is_game_over(state);
				if (!game_state.game_over && finish_state.winner != PLAYER::NONE) {
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
					game_state.game_over = true;
				}
			}

			if (key_state.space && (game_state.game_over || game_state.num_moves == 9)) {
				placed_crosses.clear();
				placed_circles.clear();
				reset_game_state(game_state);
				reset_finish_state(finish_state);
			}

			for (const rectangle_t& rectangle : rectangles) {
				draw_rectangle(rectangle);
			}

			if (!game_state.game_over && game_state.num_moves < 9) {
				if (game_state.cur_player == PLAYER::ONE) {
					temp_cross.transform.position = helper::get_ttt_box_ndc_from_idx(mouse_over_idx);
					if (state[(int)mouse_over_idx.y][(int)mouse_over_idx.x] != PLAYER::NONE) {
						temp_cross.color = temp_error_color;
					}
					else {
						temp_cross.color = temp_color;
					}
					draw_cross(temp_cross);
				}
				else {
					temp_circle.transform.position = helper::get_ttt_box_ndc_from_idx(mouse_over_idx);
					if (state[(int)mouse_over_idx.y][(int)mouse_over_idx.x] != PLAYER::NONE) {
						temp_circle.color = temp_error_color;
					}
					else {
						temp_circle.color = temp_color;
					}
					draw_outline_circle(temp_circle);
				}
			}

			for (const cross_t& cross : placed_crosses) {
				draw_cross(cross);
			}

			for (const ouline_circle_t& circle : placed_circles) {
				draw_outline_circle(circle);
			}

			if (game_state.game_over) {
				draw_rectangle(finish_line);
			}

			std::string text_at_top;
			if (game_state.game_over) {
				if (finish_state.winner == PLAYER::ONE) {
					text_at_top = "player one won!";
				}
				else if (finish_state.winner == PLAYER::TWO) {
					text_at_top = "player two won!";
				}
				else {
					text_at_top = "tied!";
				}
			}
			else if (globals.game_state->cur_player == PLAYER::ONE) {
				text_at_top = "player one";
			}
			else {
				text_at_top = "player two";
			}

			glm::vec3 top_text_scale(1.f);
			float top_text_width = get_text_width(globals.font, text_at_top, top_text_scale.x);
			float top_text_height = get_text_height(globals.font, text_at_top, top_text_scale.y);
			float title_top_y_padding = 10.f;
			draw_text(globals.font, text_at_top, (SCREEN_WIDTH - top_text_width) / 2.f, SCREEN_HEIGHT - top_text_height - title_top_y_padding, top_text_scale, text_color);

			if (game_state.game_over) {
				std::string text_on_bottom = "press spacebar to play again";
				glm::vec3 bottom_text_scale(.65f);
				float bottom_text_width = get_text_width(globals.font, text_on_bottom, bottom_text_scale.x);
				float bottom_text_bottom_y_padding = 30.f;
				draw_text(globals.font, text_on_bottom, (SCREEN_WIDTH - bottom_text_width) / 2.f, bottom_text_bottom_y_padding, bottom_text_scale, text_color);
			}
		}

		SDL_GL_SwapWindow(globals.window);
	}

	return -1;
}