#include "cross.h"
#include "helper.h"
#include <iostream>
#include "globals.h"
#include "circle.h"
#include "constants.h"

cross_t create_cross(glm::vec3 position, glm::vec3 scale, glm::vec3 color) {
	cross_t cross;
	cross.transform.position = position;
	cross.transform.scale = scale;
	cross.color = color;
	return cross;
}

void draw_cross(const cross_t& cross) {
	glm::vec3 rec_scale = glm::vec3(0.035f, .5f, 0.0f);

	rectangle_t left_diag = create_rectangle(cross.transform.position, cross.transform.scale * rec_scale, 45.0f, cross.color);
	rectangle_t right_diag = create_rectangle(cross.transform.position, cross.transform.scale * rec_scale, -45.0f, cross.color);

	const glm::vec3& cross_pos = cross.transform.position;
	float extent = cross.transform.scale.y * rec_scale.y * 0.5f;

	float x_delta = extent * cosf(glm::radians(45.0f));
	float y_delta = extent * sinf(glm::radians(45.0f));

	glm::vec3 top_left_pos = cross_pos + glm::vec3(-x_delta, y_delta, 0.f);
	glm::vec3 top_right_pos = cross_pos + glm::vec3(x_delta, y_delta, 0.f);
	glm::vec3 bottom_left_pos = cross_pos + glm::vec3(-x_delta, -y_delta, 0.f);
	glm::vec3 bottom_right_pos = cross_pos + glm::vec3(x_delta, -y_delta, 0.f);

	glm::vec2 screen_rec_size = helper::ndc_size_to_screen_size(glm::vec2(cross.transform.scale.x * rec_scale.x, cross.transform.scale.y * rec_scale.y));
	float smaller_side_screen_size = screen_rec_size.x;
	float filled_circle_screen_size = helper::ndc_size_to_screen_size(glm::vec2(FILLED_CIRCLE_RADIUS * 2.f, 0.f)).x;

	float circle_scale = smaller_side_screen_size / filled_circle_screen_size;
	filled_circle_t top_left_circle = create_filled_circle(top_left_pos, glm::vec3(circle_scale), 0.f, cross.color);
	filled_circle_t top_right_circle = create_filled_circle(top_right_pos, glm::vec3(circle_scale), 0.f, cross.color);
	filled_circle_t bottom_left_circle = create_filled_circle(bottom_left_pos, glm::vec3(circle_scale), 0.f, cross.color);
	filled_circle_t bottom_right_circle = create_filled_circle(bottom_right_pos, glm::vec3(circle_scale), 0.f, cross.color);

	draw_filled_circle(top_left_circle);
	draw_filled_circle(top_right_circle);
	draw_filled_circle(bottom_left_circle);
	draw_filled_circle(bottom_right_circle);

	draw_rectangle(left_diag);
	draw_rectangle(right_diag);
}
