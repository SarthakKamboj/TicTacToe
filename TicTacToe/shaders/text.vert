#version 410 core
layout (location = 0) in vec2 in_pos;
layout (location = 1) in vec2 in_tex_coord;

out vec2 tex_coord;
uniform mat4 projection;

void main(void)
{
    gl_Position = projection * vec4(in_pos, 0.0, 1.0);
    tex_coord = in_tex_coord;
}