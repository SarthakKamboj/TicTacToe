#include "finish_state.h"

void reset_finish_state(finish_state_t& finish_state) {
	finish_state.winner = PLAYER::NONE;
	finish_state.start_ttt_idx = glm::vec2(0, 0);
	finish_state.end_ttt_idx = glm::vec2(0, 0);
}
