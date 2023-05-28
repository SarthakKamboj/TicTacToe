#pragma once

#include <string>
#include "glm/glm.hpp"
#include "ebo.h"
#include "finish_state.h"

namespace helper {
	std::string get_file_contents(const char* path);
	glm::vec2 ndc_to_screen(const glm::vec2 ndc);
	glm::vec2 screen_to_ndc(const glm::vec2 screen);
	glm::vec2 get_ttt_box_idx_from_ndc(glm::vec2 ndc, float wall_offset);
	glm::vec3 get_ttt_box_ndc_from_idx(glm::vec2 idx);
	finish_state_t is_game_over(int state[3][3]);
	float dot_product(glm::vec3 v1, glm::vec3 v2);
}
