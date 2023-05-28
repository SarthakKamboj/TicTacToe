#pragma once

#include "glm/glm.hpp"

struct vertex_t {
	glm::vec3 position = glm::vec3(0,0,0);
	glm::vec3 color = glm::vec3(0,0,0);
	glm::vec2 tex_coord = glm::vec2(0,0);
};

vertex_t create_vertex(glm::vec3 position, glm::vec3 color, glm::vec2 tex_coord);

/*
struct Vertex {
	glm::vec3 position;
	glm::vec3 color;
	glm::vec2 texCoord;

	Vertex(glm::vec3 _position, glm::vec3 _color, glm::vec2 _texCoord) {
		position = _position;
		color = _color;
		texCoord = _texCoord;
	}

	Vertex() {
		position = glm::vec3(0, 0, 0);
		color = glm::vec3(0, 0, 0);
		texCoord = glm::vec2(0, 0);
	}
};
*/
