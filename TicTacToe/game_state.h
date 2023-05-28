#pragma once

#include "enums.h"

struct game_state_t {
	int state[3][3]{};
	int num_moves = 0;
	bool game_over = false;
	PLAYER cur_player = PLAYER::ONE;
};

void reset_game_state(game_state_t& game_state);
