#include "button.h"
#include "globals.h"
#include "font.h"
#include "rectangle.h"
#include "helper.h"
#include <iostream>

extern globals_t globals;

button_t create_button(const std::string& text, glm::vec3 text_color, glm::vec3 base_color, glm::vec3 hover_color, glm::vec3 center_pos, glm::vec3 scale, glm::vec2 padding) {
	button_t button;
	button.base_color = base_color;
	button.hover_color = hover_color;
	button.transform.scale = scale;
	button.pressed_on = false;
	button.text = text;
	button.text_color = text_color;
	button.padding = padding;
	button.center_pos = center_pos;
	float text_height = get_text_height(globals.font, text, scale.y);
	float text_min_y = get_min_text_y(globals.font, text, scale.y);
	float text_width = get_text_width(globals.font, text, scale.x);

	button.button_text_pos = center_pos - glm::vec3(text_width / 2.f, text_height / 2.f, 0.f) - glm::vec3(0.f, text_min_y, 0.f) - glm::vec3(padding, 0.f);
	// button.transform.position = button.button_text_pos - (glm::vec3(padding, 0.f) * scale);

	button.height = text_height + (padding.y * 2 * scale.y);
	button.width = text_width + (padding.x * 2 * scale.x);

	button.transform.position = center_pos - (glm::vec3(button.width, button.height, 0.f) / 2.f);

	glm::vec2 orig_top_left_corner_screen = helper::ndc_to_screen(glm::vec2(-0.5f, 0.5f));
	glm::vec2 orig_top_right_corner_screen = helper::ndc_to_screen(glm::vec2(0.5f, 0.5f));
	glm::vec2 orig_bottom_left_corner_screen = helper::ndc_to_screen(glm::vec2(-0.5f, -0.5f));

	float orig_screen_width = orig_top_right_corner_screen.x - orig_top_left_corner_screen.x;
	float orig_screen_height = orig_top_left_corner_screen.y - orig_bottom_left_corner_screen.y;
	
	button.bck_scale.x = button.width / orig_screen_width;
	button.bck_scale.y = button.height / orig_screen_height;

	return button;
}

void update_button(button_t& button, mouse_state_t& mouse_state) {	
	button.hovered_over = false;
	glm::vec2 screen_mouse = helper::mouse_to_screen(glm::vec2(mouse_state.x, mouse_state.y));
	bool within_x = (screen_mouse.x >= button.center_pos.x - button.width / 2.f) && (screen_mouse.x <= button.center_pos.x + button.width / 2.f);
	bool within_y = (screen_mouse.y >= button.center_pos.y - button.height / 2.f) && (screen_mouse.y <= button.center_pos.y + button.height / 2.f);
	button.hovered_over = within_x && within_y;
	button.pressed_on = button.hovered_over && mouse_state.mouse_up;
}

void draw_button(button_t& button) {
	transform_t& transform = button.transform;
	glm::vec3 btn_back_screen_pos = transform.position + glm::vec3(button.width / 2.f, button.height / 2.f, 0.f) - (glm::vec3(button.padding, 0.f) * button.transform.scale);
	glm::vec2 btn_ndc_pos = helper::screen_to_ndc(glm::vec2(btn_back_screen_pos.x, btn_back_screen_pos.y));
	rectangle_t bck_rec = create_rectangle(glm::vec3(btn_ndc_pos, 0.f), glm::vec3(button.bck_scale, 1.f), 0.f, button.hovered_over ? button.hover_color : button.base_color);
	draw_rectangle(bck_rec);
	draw_text(globals.font, button.text, button.button_text_pos.x, button.button_text_pos.y, transform.scale, button.text_color);
}
