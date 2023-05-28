#include "circle.h"
#include <iostream>
#include "helper.h"
#include "globals.h"

extern globals_t globals;

ouline_circle_t create_outline_circle(glm::vec3 position, glm::vec3 scale, float rot_deg, glm::vec3 color) {
	ouline_circle_t circle;
	circle.color = color;
	circle.transform.position = position;
	circle.transform.scale = scale;
	circle.transform.rotation_deg = rot_deg;
	return circle;
}

void draw_outline_circle(const ouline_circle_t& circle) {
	int vao_idx = globals.outline_circle_data.vao_idx;
	int shader_idx = globals.outline_circle_data.shader_idx;
	int ebo_idx = globals.outline_circle_data.ebo_idx;

	shader_t& shader = globals.shader_manager->shaders[shader_idx];
	vao_t& vao = globals.vao_manager->vaos[vao_idx];
	ebo_t& ebo = globals.ebo_manager->ebos[ebo_idx];

	shader_set_vec3(shader, "color", circle.color);
	shader_set_mat4(shader, "model", get_model_matrix(circle.transform));

	bind_shader(shader);
	bind_vao(vao);

	draw_ebo(ebo);
}
