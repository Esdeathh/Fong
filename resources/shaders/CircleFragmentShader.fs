#version 450 core

in vec3 color;

out vec4 aColor;

uniform vec3 center;
uniform float radius;

void main()
{
    if(distance(gl_FragCoord, vec4(center, 1.0)) > radius) discard;
    aColor = vec4(color, 1.0);
}