#version 330 core
#include "res/shaders/transforms.glsl"

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

out vec2 TexCoord;
out vec3 Normal;
out vec3 FragPosition;

void main()
{
    VertexPosition vPositions = get_vertex_positions(aPos);
    FragPosition = vPositions.WS_Position;
    gl_Position = vPositions.CS_Position;

    Normal = get_normal_positions(aNormal).WS_Normal;  
    TexCoord = aTexCoord; 
}