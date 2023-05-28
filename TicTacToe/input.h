#pragma once

#include "SDL.h"

struct key_state_t {
	bool space;
};

struct mouse_state_t {
	int x, y;
	bool mouse_up, mouse_down;
};

void handle_input(SDL_Event& event, mouse_state_t& mouse_state, key_state_t& key_state);
