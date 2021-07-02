#version 450

in vec3 position;
in vec3 instance_color;
in vec3 instance_position;

float MinPointSize = 15.0f;
float MaxPointSize = 40.0f;

out vec4 color;

float size = noise1(gl_InstanceID);

//uniform mat4 mvp;

//uniform mat4 u_MVPMatrix;

void main()
{

    gl_Position = vec4((position + instance_position), 1.0);
    color = vec4(instance_color, 1.0);
    //float size = mix(MinPointSize, MaxPointSize, gl_InstanceID);
    gl_PointSize = 20;
}

