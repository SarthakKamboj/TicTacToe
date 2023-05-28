#include "cross.h"
#include "helper.h"
#include <iostream>
#include "globals.h"

/*
Cross::Cross() {
	float v = 200 / 255.f;
	leftDiag = Rectangle(glm::vec3(0.0f), glm::vec3(0.02f, .5f, 0.0f), 45.0f, glm::vec3(v,v,v));
	rightDiag = Rectangle(glm::vec3(0.0f), glm::vec3(0.02f, .5f, 0.0f), -45.0f, glm::vec3(v,v,v));
}

Cross::Cross(const Cross& other) {
	this->leftDiag = Rectangle(other.leftDiag);
	this->rightDiag = Rectangle(other.rightDiag);
}

void Cross::draw() {
	leftDiag.draw();
	rightDiag.draw(); //   /

	// std::cout << "leftDiag.transform.position: " << vec3Str(leftDiag.transform.position) << " " << vec3Str(leftDiag.transform.scale) << " " << leftDiag.transform.rotationDeg << std::endl;
	// std::cout << "rightDiag.transform.position: " << vec3Str(rightDiag.transform.position) << " " << vec3Str(rightDiag.transform.scale) << " " << rightDiag.transform.rotationDeg << std::endl;
}

void Cross::setTransform(glm::vec3 pos) {
	leftDiag.setTransform(pos, leftDiag.transform.scale, leftDiag.transform.rotationDeg);
	rightDiag.setTransform(pos, rightDiag.transform.scale, rightDiag.transform.rotationDeg);
}

void Cross::setColor(glm::vec3 color) {
	leftDiag.setColor(color);
	rightDiag.setColor(color);
}
*/

cross_t create_cross(glm::vec3 position, glm::vec3 scale, glm::vec3 color) {
	cross_t cross;
	cross.transform.position = position;
	cross.transform.scale = scale;
	cross.color = color;
	return cross;
}

void draw_cross(const cross_t& cross) {
	rectangle_t left_diag = create_rectangle(cross.transform.position, cross.transform.scale * glm::vec3(0.035f, .5f, 0.0f), 45.0f, cross.color);
	rectangle_t right_diag = create_rectangle(cross.transform.position, cross.transform.scale * glm::vec3(0.035f, .5f, 0.0f), -45.0f, cross.color);

	draw_rectangle(left_diag);
	draw_rectangle(right_diag);
}
