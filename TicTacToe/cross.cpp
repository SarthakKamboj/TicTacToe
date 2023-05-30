#include "cross.h"
#include "helper.h"
#include <iostream>
#include "globals.h"
#include "circle.h"

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
