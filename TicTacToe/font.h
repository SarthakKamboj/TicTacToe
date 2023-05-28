#pragma once

#include "freetype/freetype.h"

struct font_t {
	FT_Face face;
};

font_t create_font(const char* font_path);
