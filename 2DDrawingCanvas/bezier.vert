#version 460

uniform mat4 ModelViewProjectionMatrix;

layout(location = 0) in vec4 Vertex;

out VertexData{
    vec4 mVertex;
} VertexOut;

void main(void)
{
    VertexOut.mVertex = Vertex;
    gl_Position = ModelViewProjectionMatrix * Vertex;
}
