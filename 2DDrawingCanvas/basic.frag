#version 450

layout (location=0) in vec3 vColor;
layout (location=0) out vec4 FragColor;

float plot(vec2 st) {
    return smoothstep(0.02, 0.0, abs(st.y - st.x));
}

void main() {

//    vec2 st = gl_FragCoord.xy/vec2(1.0f, -1.0f);

//    float y = st.x;
//    vec3 color = vec3(y);

//    // Plot a line
//    float pct = plot(st);
//    color = (1.0-pct)*color+pct*vec3(0.0,1.0,0.0);

    //gl_FragColor = vec4(vColor, 1.0);
    vec2 circCoord = 2.0 * gl_PointCoord - 1.0;
    if(dot(gl_PointCoord-0.5, gl_PointCoord-0.5) > 0.25){
        discard;
    }

    FragColor = vec4(vColor, 1.0);
    //gl_FragColor = vec4(0.0, 1.0, 0.0, 1.0);
}
