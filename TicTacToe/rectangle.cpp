#include "rectangle.h"
#include "helper.h"
#include <string>
#include <iostream>
#include "globals.h"

#define RECT_WIDTH 1.f
#define RECT_HEIGHT 1.f

/*
Rectangle::Rectangle(glm::vec3 position, glm::vec3 scale, float rotation, glm::vec3 _color, bool debugThis) {
	Vertex vertices[4];
	vertices[0] = Vertex(glm::vec3(0.5f, 0.5f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f));
	vertices[1] = Vertex(glm::vec3(0.5f, -0.5f, 0.0f),glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.f, 0.0f));
	vertices[2] = Vertex(glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.f));
	vertices[3] = Vertex(glm::vec3(-0.5f, 0.5f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(0.0f, 1.f));

	vbo = VBO((float*)vertices, sizeof(vertices));

	unsigned int indices[] = {
		0, 1, 3,
		1, 2, 3
	};

	getAllEBOVerts();
	ebo = EBO(indices, sizeof(indices));
	getAllEBOVerts();
	std::cout << "ebo: " << ebo.id << std::endl;

	if (!debugThis) {
		vao.bind();
		vao.enableAttribute(vbo, 0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
		vao.enableAttribute(vbo, 1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), offsetof(Vertex, color));
		vao.enableAttribute(vbo, 2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), offsetof(Vertex, texCoord));
		ebo.bind();
		vao.unbind();
		ebo.unbind();

		shader = Shader("C:\\Sarthak\\projects\\TicTacToe\\TicTacToe\\basic.vert", "C:\\Sarthak\\projects\\TicTacToe\\TicTacToe\\basic.frag");
		color = _color;
		shader.setVec3("color", color);

		transform = Transform(position, scale, rotation);
		shader.setMat4("model", transform.getModelMatrix());
	}
}

Rectangle::Rectangle(const Rectangle& other) {
	memcpy(this, &other, sizeof(Rectangle));
	shader = Shader("C:\\Sarthak\\projects\\TicTacToe\\TicTacToe\\basic.vert", "C:\\Sarthak\\projects\\TicTacToe\\TicTacToe\\basic.frag");
	shader.setVec3("color", color);
	shader.setMat4("model", transform.getModelMatrix());
}

void Rectangle::draw() {
	// glm::vec3 color = shader.getVec3("color");
	shader.bind();
	vao.bind();
	glDrawElements(GL_TRIANGLES, ebo.numIndicies, GL_UNSIGNED_INT, 0);
}

void Rectangle::setTransform(glm::vec3 position, glm::vec3 scale, float rotation) {
	transform = Transform(position, scale, rotation);
	shader.setMat4("model", transform.getModelMatrix());
}

void Rectangle::setColor(glm::vec3 _color) {
	std::cout << "color changed from " << vec3Str(color) << " to " << vec3Str(_color) << std::endl;
	shader.setVec3("color", _color);
	color = _color;
}
*/

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
