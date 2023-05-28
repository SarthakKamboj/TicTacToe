#pragma once

#include "transform.h"
#include "vertex.h"
#include "vao.h"
#include "vbo.h"
#include "ebo.h"
#include "shader.h"

struct rectangle_t {
	transform_t transform;
	glm::vec3 color;
};

rectangle_t create_rectangle(glm::vec3 position, glm::vec3 scale, float rot_deg, glm::vec3 color);
void draw_rectangle(const rectangle_t& rectangle);
