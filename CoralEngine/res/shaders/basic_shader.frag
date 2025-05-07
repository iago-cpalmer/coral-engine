#version 330 core
#include "res/shaders/basic_material.glsl"
#include "res/shaders/lights.glsl"
out vec4 FragColor;

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPosition;

uniform Material uMaterial;

uniform vec3 uViewPosition;

void main()
{
    FragColor = texture(uMaterial.AlbedoMap, TexCoord);

    FragColor = (compute_directional_light_color(Normal, FragPosition, uViewPosition, uMaterial) + compute_point_light_color(Normal, FragPosition, uViewPosition, uMaterial)) * FragColor; 
} 