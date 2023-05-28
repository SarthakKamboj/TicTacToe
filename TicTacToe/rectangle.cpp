#include "rectangle.h"
#include "helper.h"
#include <string>
#include <iostream>
#include "globals.h"

#define RECT_WIDTH 1.f
#define RECT_HEIGHT 1.f

extern globals_t globals;

rectangle_t create_rectangle(glm::vec3 position, glm::vec3 scale, float rot_deg, glm::vec3 color) {
	rectangle_t rectangle;
	rectangle.color = color;
	rectangle.transform.position = position;
	rectangle.transform.scale = scale;
	rectangle.transform.rotation_deg = rot_deg;
	return rectangle;
}

void draw_rectangle(const rectangle_t& rectangle) {
	int vao_idx = globals.rectangle_data.vao_idx;
	int shader_idx = globals.rectangle_data.shader_idx;
	int ebo_idx = globals.rectangle_data.ebo_idx;

	shader_t& shader = globals.shader_manager->shaders[shader_idx];
	vao_t& vao = globals.vao_manager->vaos[vao_idx];
	int num_indicies = globals.ebo_manager->ebos[ebo_idx].numIndicies;

	shader_set_vec3(shader, "color", rectangle.color);
	shader_set_mat4(shader, "model", get_model_matrix(rectangle.transform));

	bind_shader(shader);
	bind_vao(vao);

	glDrawElements(GL_TRIANGLES, num_indicies, GL_UNSIGNED_INT, 0);
}
