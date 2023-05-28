#include "input.h"

void handle_input(SDL_Event& event, mouse_state_t& mouse_state, key_state_t& key_state) {

	switch (event.type) {
	case SDL_MOUSEBUTTONUP: {
		mouse_state.mouse_up = true;
	}
						  break;
	case SDL_MOUSEBUTTONDOWN: {
		mouse_state.mouse_down = true;
	}
							break;
	case SDL_KEYDOWN: {
		switch (event.key.keysym.sym) {
		case SDLK_SPACE: {
			key_state.space = true;
			break;
		}
		default:
			break;
		}
	}
					break;
	default:
		break;
	}
}
