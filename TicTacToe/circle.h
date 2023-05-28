#pragma once

#include "vao.h"
#include "vbo.h"
#include "ebo.h"
#include <vector>
#include "vertex.h"
#include "shader.h"
#include "transform.h"

/*
class OutlineCircle {
public:
	OutlineCircle() = default;
	OutlineCircle(const OutlineCircle& other);
	OutlineCircle(int numPoints, float innerRadius, float outerRadius, glm::vec3 color);
	VAO vao;
	VBO vbo;
	EBO ebo;
	Shader shader;
	Transform transform;
	glm::vec3 color;
	void draw();
	void setTransform(glm::vec3 position);
	void setColor(glm::vec3 color);
};

class FilledCircle {
public:
	FilledCircle() = default;
	FilledCircle(const FilledCircle& other);
	FilledCircle(int numPoints, float radius, glm::vec3 color);
	VAO vao;
	VBO vbo;
	EBO ebo;
	Shader shader;
	Transform transform;
	glm::vec3 color;
	void draw();
	void setTransform(glm::vec3 position);
	void setColor(glm::vec3 color);
};
*/

struct ouline_circle_t {
	transform_t transform;
	glm::vec3 color;
};

ouline_circle_t create_outline_circle(glm::vec3 position, glm::vec3 scale, float rot_deg, glm::vec3 color);
void draw_outline_circle(const ouline_circle_t& circle);
