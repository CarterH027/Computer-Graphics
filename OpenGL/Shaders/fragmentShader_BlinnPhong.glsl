#version 330 core

layout(location=0) out vec4 fragmentColor;

uniform vec3 diffuseComponent;
uniform float phongExp;
uniform vec3 viewDir;
uniform vec3 lightIntensity;
uniform vec3 specCoef;
uniform vec3 viewPos;

in vec4 normal;
in vec4 lightDir;
in vec4 vertexWorldPos;

void main(void)
{
    vec3 N = normalize(vec3(normal));
    vec3 L = normalize(vec3(lightDir));
    vec3 V = normalize(viewPos - vec3(vertexWorldPos));

    float val = max(0.0, dot(N, L));
    vec3 diffuseShading = diffuseComponent * val * lightIntensity;

    vec3 specular = vec3(0.0);
    if (val > 0.0) {
        vec3 halfVector = normalize(L + V);
        float spec = pow(max(dot(N, halfVector), 0.0), phongExp);
        specular = specCoef * spec * lightIntensity;
    }

    vec3 finalColor = diffuseShading + specular;

    fragmentColor = vec4(finalColor, 1.0);
}