#version 410 core

out vec4 FragColor;
  
in vec3 ourColor;
in vec2 TexCoord;

uniform vec3 color;

void main(void)
{
    FragColor = vec4(color, 1.0);
}