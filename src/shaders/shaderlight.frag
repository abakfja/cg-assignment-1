#version 330 core

// Interpolated values from the vertex shaders
in vec3 fragColor;
in vec3 fragPos;
in vec3 normal;

uniform vec3 lightPos;// changes with player
uniform vec3 viewPos;// changes with player
uniform vec3 lightColor;// set once
uniform float diffuseStrength;// changes with mode
uniform float ambientStrength;// changes with mode
// output data
out vec3 color;


void main()
{
    // Output color = color specified in the vertex shader,
    // interpolated between all 3 surrounding vertices of the triangle
    vec3 ambient = ambientStrength * lightColor;

    vec3 norm = normalize(normal);
    float dist = length(fragPos - lightPos) + 0.1;
    float invsq = 1.0 / (dist *dist);
    vec3 lightDir = normalize(lightPos - fragPos);
    float diff = max(dot(norm, lightDir), 0.2);
    vec3 diffuse = invsq * diff * diffuseStrength * lightColor;
    float specularStrength = diffuseStrength / dist;
    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 0.5);
    vec3 specular = specularStrength * spec * lightColor;
    color = (ambientStrength + specular + diffuse) * fragColor;
}
