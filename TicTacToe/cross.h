#pragma once

#include "rectangle.h"

struct cross_t {
	transform_t transform;
	glm::vec3 color;
};

cross_t create_cross(glm::vec3 pos, glm::vec3 scale, glm::vec3 color);
void draw_cross(const cross_t& cross);
