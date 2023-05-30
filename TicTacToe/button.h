#pragma once

#include <string>
#include "glm/glm.hpp"
#include "transform.h"
#include "input.h"

struct button_t {
	std::string text = "";
	// position is for bottom left in screen coordinates
	transform_t transform;
	// position for text in bottom left screen
	glm::vec3 button_text_pos;
	glm::vec3 text_color = glm::vec3(0);
	glm::vec3 base_color = glm::vec3(0);
	glm::vec3 hover_color = glm::vec3(0);
	glm::vec2 padding;
	glm::vec2 bck_scale = glm::vec2(0);
	glm::vec2 center_pos;
	float width;
	float height;
	bool pressed_on = false;
	bool hovered_over = false;
};

button_t create_button(const std::string& text, glm::vec3 text_color, glm::vec3 base_color, glm::vec3 hover_color, glm::vec3 center_pos, glm::vec3 scale, glm::vec2 padding);
void update_button(button_t& button, mouse_state_t& mouse_state);
void draw_button(button_t& button);
