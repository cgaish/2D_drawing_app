#version 450

layout (location=0) in vec3 l_VertexPosition;
layout (location=1) in vec3 l_VertexColor;

layout (location=0) out vec3 l_vColor;

uniform mat4 u_MVPMatrix;

void main()
{
    l_vColor = l_VertexColor;

    gl_Position = u_MVPMatrix * vec4(l_VertexPosition,1.0);
    gl_PointSize = 10.0f;
}

