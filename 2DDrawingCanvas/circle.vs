#version 450

layout (location = 0 ) in vec2 VertexPosition;
layout (location = 1 ) in vec3 VertexColor;
layout (location = 2 ) in float CircleSides;

out vec3 vColor;
out float cSides;

void main()
{
    gl_Position = vec4(VertexPosition, 0.0, 1.0);\
    vColor = VertexColor;
    cSides = CircleSides;
}
