#version 410 core
layout (location = 0) in vec3 in_pos;

uniform mat4 model;

void main(void)
{
    gl_Position = model * vec4(in_pos, 1.0);
}