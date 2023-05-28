#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

struct transform_t {
	glm::vec3 position = glm::vec3(0,0,0); 
	glm::vec3 scale = glm::vec3(0,0,0);
	float rotation_deg = 0;
};

transform_t create_transform(glm::vec3 position, glm::vec3 scale, float rot_deg);
glm::mat4 get_model_matrix(const transform_t& transform);
