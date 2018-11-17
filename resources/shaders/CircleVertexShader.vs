#version 450 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 aColor;

uniform mat4 world;
uniform mat4 projection;

out vec3 color;

void main()
{
    gl_Position = projection * world * vec4(position, 1.0);
    color = aColor;
}