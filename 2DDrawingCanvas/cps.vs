#version 400

in vec4 VertexPosition;

uniform mat4 MVP;

void main()
{
    gl_Position = MVP * VertexPosition;
}
