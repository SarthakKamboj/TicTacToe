#include "transform.h"

transform_t create_transform(glm::vec3 position, glm::vec3 scale, float rot_deg) {
	transform_t transform;
	transform.position = position;
	transform.scale = scale;
	transform.rotation_deg = rot_deg;
	return transform;
}

glm::mat4 get_model_matrix(const transform_t& transform) {
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, transform.position);
	model = glm::rotate(model, glm::radians(transform.rotation_deg), glm::vec3(0.f, 0.f, 1.0f));
	const glm::vec3& scale = transform.scale;
	model = glm::scale(model, glm::vec3(scale.x, scale.y, 0.0f));
	return model;
}
