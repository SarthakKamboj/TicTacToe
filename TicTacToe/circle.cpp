#include "circle.h"
#include <iostream>
#include "helper.h"
#include "globals.h"

/*
OutlineCircle::OutlineCircle(int numPoints, float innerRadius, float outerRadius, glm::vec3 color) {
	if (numPoints < 3) {
		throw std::exception("not enough points");
	}
	if (innerRadius > outerRadius) {
		throw std::exception("inner radius bigger than outer radius");
	}

	float angleIter = 2 * PI / numPoints;

	std::vector<Vertex> vertices;
	std::vector<int> indicies;

	for (int i = 0; i < numPoints; i++) {
		Vertex bottomLeft, bottomRight, topLeft, topRight;
		float angle = angleIter * i;
		bottomLeft.position = glm::vec3(innerRadius * cosf(angle + angleIter), innerRadius * sinf(angle + angleIter), 0.0f);
		bottomRight.position = glm::vec3(innerRadius * cosf(angle), innerRadius * sinf(angle), 0.0f);
		topLeft.position = glm::vec3(outerRadius * cosf(angle + angleIter), outerRadius * sinf(angle + angleIter), 0.0f);
		topRight.position = glm::vec3(outerRadius * cosf(angle), outerRadius * sinf(angle), 0.0f);

		int curLen = vertices.size();

		vertices.push_back(bottomLeft);
		vertices.push_back(bottomRight);
		vertices.push_back(topLeft);
		vertices.push_back(topRight);

		int bottomLeftIdx = curLen;
		int bottomRightIdx = curLen + 1;
		int topLeftIdx = curLen + 2;
		int topRightIdx = curLen + 3;

		indicies.push_back(bottomLeftIdx);
		indicies.push_back(topLeftIdx);
		indicies.push_back(topRightIdx);
		indicies.push_back(topRightIdx);
		indicies.push_back(bottomRightIdx);
		indicies.push_back(bottomLeftIdx);
	}

	vbo = VBO((float*)vertices.data(), vertices.size() * sizeof(vertices[0]));
	ebo = EBO((unsigned int*)indicies.data(), indicies.size() * sizeof(indicies[0]));

	vao.bind();
	vao.enableAttribute(vbo, 0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	vao.enableAttribute(vbo, 1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), offsetof(Vertex, color));
	vao.enableAttribute(vbo, 2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), offsetof(Vertex, texCoord));
	ebo.bind();
	vao.unbind();
	ebo.unbind();

	shader = Shader("C:\\Sarthak\\projects\\TicTacToe\\TicTacToe\\basic.vert", "C:\\Sarthak\\projects\\TicTacToe\\TicTacToe\\basic.frag");
	this->color = color;
	shader.setVec3("color", color);

	transform = Transform(glm::vec3(0.f), glm::vec3(1.0f), 0.0f);
	shader.setMat4("model", transform.getModelMatrix());
}

OutlineCircle::OutlineCircle(const OutlineCircle& other) {
	memcpy(this, &other, sizeof(OutlineCircle));
	shader = Shader("C:\\Sarthak\\projects\\TicTacToe\\TicTacToe\\basic.vert", "C:\\Sarthak\\projects\\TicTacToe\\TicTacToe\\basic.frag");
	shader.setVec3("color", color);
	shader.setMat4("model", transform.getModelMatrix());
}

void OutlineCircle::draw() {
	shader.bind();
	vao.bind();
	glDrawElements(GL_TRIANGLES, ebo.numIndicies, GL_UNSIGNED_INT, 0);
}

void OutlineCircle::setTransform(glm::vec3 position) {
	transform = Transform(position, glm::vec3(1.0f), 0.0f);
	shader.setMat4("model", transform.getModelMatrix());
}

void OutlineCircle::setColor(glm::vec3 _color) {
	std::cout << "color changed from " << vec3Str(color) << " to " << vec3Str(_color) << std::endl;
	color = _color;
	shader.setVec3("color", color);
}

FilledCircle::FilledCircle(int numPoints, float radius, glm::vec3 color) {
	if (numPoints < 3) {
		throw std::exception("not enough points");
	}

	float angleIter = 2 * PI / numPoints;

	std::vector<Vertex> vertices;
	Vertex center;
	center.position = { 0,0,0 };
	center.color = color;
	center.texCoord = { 0,0 };
	vertices.push_back(center);

	this->color = color;

	std::vector<int> indicies;

	for (int i = 0; i < numPoints; i++) {
		Vertex left, right;
		float angle = angleIter * i;
		left.position = glm::vec3(radius * cosf(angle + angleIter), radius * sinf(angle + angleIter), 0.0f);
		right.position = glm::vec3(radius * cosf(angle), radius * sinf(angle), 0.0f);

		left.color = color;
		right.color = color;

		int curLen = vertices.size();

		vertices.push_back(left);
		vertices.push_back(right);

		int leftIdx = curLen;
		int rightIdx = curLen + 1;

		indicies.push_back(0);
		indicies.push_back(leftIdx);
		indicies.push_back(rightIdx);
	}

	vbo = VBO((float*)vertices.data(), vertices.size() * sizeof(vertices[0]));
	ebo = EBO((unsigned int*)indicies.data(), indicies.size() * sizeof(indicies[0]));

	vao.bind();
	vao.enableAttribute(vbo, 0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	vao.enableAttribute(vbo, 1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), offsetof(Vertex, color));
	vao.enableAttribute(vbo, 2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), offsetof(Vertex, texCoord));
	ebo.bind();
	vao.unbind();
	ebo.unbind();

	shader = Shader("C:\\Sarthak\\projects\\TicTacToe\\TicTacToe\\basic.vert", "C:\\Sarthak\\projects\\TicTacToe\\TicTacToe\\basic.frag");
	shader.setVec3("color", color);

	transform = Transform(glm::vec3(0.f), glm::vec3(1.0f), 0.0f);
	shader.setMat4("model", transform.getModelMatrix());
}

FilledCircle::FilledCircle(const FilledCircle& other) {
	memcpy(this, &other, sizeof(FilledCircle));
	shader = Shader("C:\\Sarthak\\projects\\TicTacToe\\TicTacToe\\basic.vert", "C:\\Sarthak\\projects\\TicTacToe\\TicTacToe\\basic.frag");
	shader.setVec3("color", color);
	shader.setMat4("model", transform.getModelMatrix());
}

void FilledCircle::draw() {
	shader.bind();
	vao.bind();
	glDrawElements(GL_TRIANGLES, ebo.numIndicies, GL_UNSIGNED_INT, 0);
}

void FilledCircle::setTransform(glm::vec3 position) {
	transform = Transform(position, glm::vec3(1.0f), 0.0f);
	shader.setMat4("model", transform.getModelMatrix());
}

void FilledCircle::setColor(glm::vec3 _color) {
	color = _color;
	shader.setVec3("color", color);
}

*/

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
	int num_indicies = globals.ebo_manager->ebos[ebo_idx].numIndicies;

	shader_set_vec3(shader, "color", circle.color);
	shader_set_mat4(shader, "model", get_model_matrix(circle.transform));

	bind_shader(shader);
	bind_vao(vao);

	glDrawElements(GL_TRIANGLES, num_indicies, GL_UNSIGNED_INT, 0);
}
