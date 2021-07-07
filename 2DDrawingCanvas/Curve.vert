#version 450

in vec3 position;
uniform mat4 MVP;
out vec4 color;
//out vec4 mVertex;

void main()
{
    gl_Position = MVP * vec4(position, 1.0);
//    mVertex = vec4(position, 1.0);
    color = vec4(0.5, 0.5, 0.0, 1.0);
}
