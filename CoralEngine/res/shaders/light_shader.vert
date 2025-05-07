#version 330 core
#include "res/shaders/transforms.glsl"

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec2 TexCoord;

void main()
{
    VertexPosition vPositions = get_vertex_positions(aPos);
    gl_Position = vPositions.CS_Position;

    TexCoord = aTexCoord; 
}