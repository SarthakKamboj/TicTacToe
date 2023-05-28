#pragma once

#include "vao.h"
#include "vbo.h"
#include "ebo.h"
#include <vector>
#include "vertex.h"
#include "shader.h"
#include "transform.h"

struct ouline_circle_t {
	transform_t transform;
	glm::vec3 color;
};

ouline_circle_t create_outline_circle(glm::vec3 position, glm::vec3 scale, float rot_deg, glm::vec3 color);
void draw_outline_circle(const ouline_circle_t& circle);
