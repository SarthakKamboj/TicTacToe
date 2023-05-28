#pragma once

#include "transform.h"
#include "vertex.h"
#include "vao.h"
#include "vbo.h"
#include "ebo.h"
#include "shader.h"

/*
class Rectangle {
public:
	Rectangle() = default;
	Rectangle(const Rectangle& other);
	Rectangle(glm::vec3 position, glm::vec3 scale, float rotation, glm::vec3 _color, bool debugThis = false);
	void draw();
	void setColor(glm::vec3 color);
	void setTransform(glm::vec3 position, glm::vec3 scale, float rotation);

	VAO vao;
	VBO vbo;
	EBO ebo;
	Shader shader;
	glm::vec3 color;

	Transform transform;
};
*/

struct rectangle_t {
	transform_t transform;
	glm::vec3 color;
};

rectangle_t create_rectangle(glm::vec3 position, glm::vec3 scale, float rot_deg, glm::vec3 color);
void draw_rectangle(const rectangle_t& rectangle);
