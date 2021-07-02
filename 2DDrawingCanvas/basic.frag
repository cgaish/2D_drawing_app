#version 450

in vec4 color;
out vec4 fcolor;

//float max_time = 100000000.0;

//float box(in vec2 _st, in vec2 _size){
//    _size = vec2(0.5) - _size*0.5;
//    vec2 uv = smoothstep(_size,
//                        _size+vec2(0.001),
//                        _st);
//    uv *= smoothstep(_size,
//                    _size+vec2(0.001),
//                    vec2(1.0)-_st);
//    return uv.x*uv.y;
//}

//float cross(in vec2 _st, float _size){
//    return  box(_st, vec2(_size,_size/4.)) +
//            box(_st, vec2(_size/4.,_size));
//}

void main() {
//    vec3 color = vec3(0.0);
//    const vec4 color1 = vec4(0.6, 0.0, 0.0, 1.0);
//    const vec4 color2 = vec4(0.9, 0.7, 1.0, 0.0);

//    vec2 temp = gl_PointCoord - vec2(0.5);
//    float f = dot(temp, temp);

//    if (f > 0.25)
//        discard;
    vec2 circCoord = 2.0 * gl_PointCoord - 1.0;
    if(dot(gl_PointCoord-0.5, gl_PointCoord-0.5) > 0.25){
        discard;
    }
//    vec2 st = gl_FragCoord.xy;
//    for(int i = 0; i < max_time; i++)
//    {

//        vec2 translate = vec2(cos(i), sin(i));
//        st += translate*0.35;
//        color += vec4(vec3(cross(st, 0.25)), 1.0);
//        fcolor = color;
//    }
    FragColor = color;


}
