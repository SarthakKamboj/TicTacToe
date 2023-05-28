#include "game_state.h"
#include <iostream>

void reset_game_state(game_state_t& game_state) {
	memset(&game_state, 0, sizeof(game_state_t));
	game_state.cur_player = PLAYER::ONE;
}