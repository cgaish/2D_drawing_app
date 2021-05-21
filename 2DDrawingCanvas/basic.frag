#version 460

layout (location=0) in vec3 vColor;
layout (location=0) out vec4 FragColor;



void main() {
    vec2 circCoord = 2.0 * gl_PointCoord - 1.0;
    if(dot(gl_PointCoord-0.5, gl_PointCoord-0.5) > 0.25)
        discard;
    else
        FragColor = vec4(vColor, 1.0);

}
