#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 aTexCoord;

out vec2 TexCoord;

uniform mat4 world;
uniform mat4 projection;

void main()
{
    gl_Position = projection * world * vec4(position, 1.0);
    TexCoord = aTexCoord;
}