#include "font.h"
#include "globals.h"
#include <iostream>
#include "transform.h"
#include "vbo.h"
#include "vertex.h"
#include <cmath>

extern globals_t globals;

font_t create_font(const char* font_path) {
	font_t font;
	FT_Error error = FT_New_Face(globals.ft_library, font_path, 0, &font.face);
	if (error) {
		const char* err_char = FT_Error_String(error);
		std::cout << "ERROR::FREETYPE: Failed to load font " << "\n" << err_char << std::endl;
		return font;
	}
	FT_Set_Pixel_Sizes(font.face, 0, 48);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	for (unsigned char c = 0; c < 128; c++) {
		FT_Error load_error = FT_Load_Char(font.face, c, FT_LOAD_RENDER);
		if (load_error) {
			std::cout << "ERROR::FREETYTPE: Failed to load Glyph " << std::to_string(c) << std::endl;
			continue;
		}
		character_t character;
		glGenTextures(1, &character.texture);
		glBindTexture(GL_TEXTURE_2D, character.texture);
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RED,
			font.face->glyph->bitmap.width,
			font.face->glyph->bitmap.rows,
			0,
			GL_RED,
			GL_UNSIGNED_BYTE,
			font.face->glyph->bitmap.buffer
		);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// font.face->glyph->advance.x is number of (1/64) pixels
		character.advance = (float)(font.face->glyph->advance.x >> 6);
		character.bearing = glm::ivec2(font.face->glyph->bitmap_left, font.face->glyph->bitmap_top);
		character.dimensions = glm::ivec2(font.face->glyph->bitmap.width, font.face->glyph->bitmap.rows);

		glBindTexture(GL_TEXTURE_2D, 0);

		font.character_map.insert(std::pair<char, character_t>(c, character));
	}
	
	return font;
}

void draw_text(const font_t& font, const std::string& text, float x, float y, glm::vec3& scale, glm::vec3& color) {
	int vao_idx = globals.text_quad_data.vao_idx;
	int shader_idx = globals.text_quad_data.shader_idx;
	int ebo_idx = globals.text_quad_data.ebo_idx;
	int vbo_idx = globals.text_quad_data.vbo_idx;

	shader_t& shader = globals.shader_manager->shaders[shader_idx];
	vao_t& vao = globals.vao_manager->vaos[vao_idx];
	vbo_t& vbo = globals.vbo_manager->vbos[vbo_idx];
	ebo_t& ebo = globals.ebo_manager->ebos[ebo_idx];

	shader_set_vec3(shader, "color", color);
	bind_shader(shader);
	bind_vao(vao);

	for (int i = 0; i < text.size(); i++) {
		char c = (char)text[i];
		const character_t& char_data = font.character_map.at(c);

		float start_x = x + (char_data.bearing.x * scale.x);
		float start_y = y - (char_data.dimensions.y - char_data.bearing.y) * scale.y;
		float width = char_data.dimensions.x * scale.x;
		float height = char_data.dimensions.y * scale.y;

		/*

			FREETYPE FONT TEXTURE RENDERED UPSIDE DOWN
			EXAMPLE) h
			|  |
			|  |
			|__|
			| 
			| 
			FOR
			| 
			|__  
			|  |
			|  |
			|  |
		*/
		vertex_t vertices[4];
		vertices[0] = create_vertex(glm::vec3(start_x + width, start_y + height, 0.f), glm::vec3(0.f), glm::vec2(1.0f, 0.0f)); // top right
		vertices[1] = create_vertex(glm::vec3(start_x + width, start_y, 0.f), glm::vec3(0.f), glm::vec2(1.f, 1.0f)); // bottom right
		vertices[2] = create_vertex(glm::vec3(start_x, start_y, 0.f), glm::vec3(0.f), glm::vec2(0.0f, 1.f)); // bottom left
		vertices[3] = create_vertex(glm::vec3(start_x, start_y  + height, 0.f), glm::vec3(0.f), glm::vec2(0.0f, 0.f)); // top left

		update_vbo_data(vbo, (float*)vertices, sizeof(vertices));
			
		glBindTexture(GL_TEXTURE_2D, char_data.texture);
		draw_ebo(ebo);

		x += char_data.advance * scale.x;
	}
}

float get_text_width(const font_t& font, const std::string& text, float scale) {
	float width = 0.f;
	for (int i = 0; i < text.size(); i++) {
		char c = (char)text[i];
		const character_t& char_data = font.character_map.at(c);
		width += char_data.advance;
	}
	return width * scale;
}

float get_text_height(const font_t& font, const std::string& text, float scale) {
	float max_y_bearing = 0.0f;
	float y_min = 0.0f;

	for (int i = 0; i < text.size(); i++) {
		char c = (char)text[i];
		const character_t& char_data = font.character_map.at(c);
		max_y_bearing = fmax(max_y_bearing, char_data.bearing.y);
		float cur_y_min = char_data.dimensions.y - char_data.bearing.y;
		y_min = fmin(y_min, cur_y_min);
	}

	return (max_y_bearing - y_min) * scale;
}

float get_char_width_w_padding(const font_t& font, const char c, float scale) {
	return font.character_map.at(c).advance * scale;
}
