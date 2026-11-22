#version 330 core

layout(location=0) out vec4 fragmentColor;

in vec4 normal;


void main(void)
{
    vec3 color = vec3(normal.x, normal.y, normal.z);

    fragmentColor = vec4(color, 1.0);
}