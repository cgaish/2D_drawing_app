#version 450

layout(lines) in;
layout(line_strip, max_vertices = 124) out;

in vec4 color[];
//in vec4 mVertex[];
out vec4 fColor;

void main()
{

    float thickness = 3.0;
    for (int i = 0; i<gl_in.length(); i++)
    {
       fColor = color[i];
       gl_Position = gl_in[i].gl_Position;
       EmitVertex();
    }

    EndPrimitive();
}
