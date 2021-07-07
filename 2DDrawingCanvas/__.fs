#version 450
in vec4 color;
in VertexData{
    vec4 mColor;
    vec4 mVertex;
}VertexIn;

void main(void){
    gl_FragColor = color;
}
