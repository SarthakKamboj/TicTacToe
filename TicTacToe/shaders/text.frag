#version 410 core

out vec4 frag_color;

uniform vec3 color;
uniform sampler2D char_texture;
in vec2 tex_coord;

void main() {
	float alpha = texture(char_texture, tex_coord).r;
	frag_color = vec4(color, alpha);
}