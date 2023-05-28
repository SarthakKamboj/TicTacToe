#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

/*
struct Transform {
	glm::vec3 position;
	glm::vec3 scale;
	float rotationDeg;

	Transform() {
		position = glm::vec3(0, 0, 0);
		scale = glm::vec3(0, 0, 0);
		rotationDeg = 0;
	}

	Transform(glm::vec3 _position, glm::vec3 _scale, float _rot) {
		position = _position;
		scale = _scale;
		rotationDeg = _rot;
	}

	glm::mat4 getModelMatrix() {
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, position);
		model = glm::rotate(model, glm::radians(rotationDeg), glm::vec3(0.f, 0.f, 1.0f));
		model = glm::scale(model, glm::vec3(scale.x, scale.y, 0.0f));
		return model;
	}
};
*/

struct transform_t {
	glm::vec3 position = glm::vec3(0,0,0); 
	glm::vec3 scale = glm::vec3(0,0,0);
	float rotation_deg = 0;
};

transform_t create_transform(glm::vec3 position, glm::vec3 scale, float rot_deg);
glm::mat4 get_model_matrix(const transform_t& transform);
