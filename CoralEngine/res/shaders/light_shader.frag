#version 330 core
#include "res/shaders/basic_material.glsl"
#include "res/shaders/lights.glsl"
out vec4 FragColor;

in vec2 TexCoord;

uniform Material uMaterial;

void main()
{
    FragColor = texture(uMaterial.AlbedoMap, TexCoord);
} 