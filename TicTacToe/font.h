#pragma once

#include "freetype/freetype.h"
#include "glad/glad.h"
#include <map>
#include "glm/glm.hpp"
#include <string>

struct character_t {
	GLuint texture = 0;
	glm::ivec2 dimensions = glm::ivec2(0,0);
	glm::ivec2 bearing = glm::ivec2(0,0);
	float advance = 0.f;
};

struct font_t {
	FT_Face face;
	std::map<char, character_t> character_map;
};

font_t create_font(const char* font_path);
void draw_text(const font_t& font, const std::string& text, float x, float y, glm::vec3& scale, glm::vec3& color);
float get_text_width(const font_t& font, const std::string& text, float scale_width);
float get_char_width_w_padding(const font_t& font, const char c, float scale_width);
float get_text_height(const font_t& font, const std::string& text, float scale_height);
float get_min_text_y(const font_t& font, const std::string& text, float scale_height);
float get_max_text_y_bearing(const font_t& font, const std::string& text, float scale_height);
