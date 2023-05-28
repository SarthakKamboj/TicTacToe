#include "font.h"
#include "globals.h"
#include <iostream>

extern globals_t globals;

font_t create_font(const char* font_path) {
	font_t font;
	if (FT_New_Face(globals.ft_library, font_path, 0, &font.face)) {
		std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
		return font;
	}
	FT_Set_Pixel_Sizes(font.face, 0, 48);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	
	return font;
}
