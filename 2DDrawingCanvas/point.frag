#version 450

in vec4 color;
out vec4 fcolor;


void main() {
//    vec2 circCoord = 2.0 * gl_PointCoord - 1.0;
//    if(dot(gl_PointCoord-0.5, gl_PointCoord-0.5) > 0.25){
//        discard;
//    }

    fcolor = color;
}
