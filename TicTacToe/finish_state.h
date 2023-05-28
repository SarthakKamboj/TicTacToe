#pragma once

#include "glm/glm.hpp"

struct finish_state_t {
	int winner = -1;
	glm::vec2 start_ttt_idx = glm::vec2(0,0);
	glm::vec2 end_ttt_idx = glm::vec2(0,0);
};