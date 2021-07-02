#version 450

layout(lines) in;
layout(line_strip, max_vertices = 4) out;
vec3 getNormal(vec3 pt1, vec3 pt2){
    return normalize(cross(pt1, pt2));
}
void main()
{
    float thickness = 3.0;
    for (int i = 0; i<gl_in.length(); i++)
    {

       gl_Position = gl_in[i].gl_Position;
//       vec3 direction = getNormal(gl_in[i].gl_Position, gl_in[i + 1].gl_Position) * thickness;
       //vec3 direction = normalize(gl_in[i].gl_Position) * thickness;
//       gl_Position = vec4(direction, 0.0);
       EmitVertex();
    }

    EndPrimitive();
}
