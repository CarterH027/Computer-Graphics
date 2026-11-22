#version 330 core

layout(location=0) out vec4 fragmentColor;

uniform vec3 diffuseComponent;
uniform vec3 lightIntensity;

in vec4 normal;
in vec4 lightDir;

void main(void)
{
    vec3 N = normalize(vec3(normal));
    vec3 L = normalize(vec3(lightDir));

    float val = max(0.0f, dot(N, L));
    vec3 diffuseShading = vec3( diffuseComponent.r * val, diffuseComponent.g * val, diffuseComponent.b * val ) * lightIntensity;

    fragmentColor = vec4(diffuseShading, 1.0);
}