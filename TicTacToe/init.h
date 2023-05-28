#pragma once

#include <vector>
#include "rectangle.h"

void init();
void init_managers();
void init_sdl();
void init_rectangle_data();
void init_outline_circle_data(int num_points, float inner_radius, float outer_radius);
void init_freetype();
void setup_board_objects(std::vector<rectangle_t>& rectangles);
