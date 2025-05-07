#ifndef RENDERER_H
#define RENDERER_H

#include "../core/window.h"
#include "../renderer/camera.h"
#include <glm/ext/matrix_float4x4.hpp>


//#define WIREFRAME_MODE

typedef struct
{
	glm::vec2 ViewportSizePx;
} RenderData;

// TODO: this renderer data should not be global. It should be static inside the cpp file.
// Now is done this way as it's needed in main.cpp, inside the main loop, to pass matrices
// to shaders.
extern RenderData RendererData;

void renderer_init_opengl();

void renderer_set_clear_color_normalized(float r, float g, float b);
void renderer_set_clear_color(float r, float g, float b);

void renderer_prepare_frame();
void renderer_finish_render();

void renderer_change_viewport_callback(int rWidth, int rHeight);


void draw_indexed(unsigned int vao, unsigned int ebo, unsigned int indexNr);

#if _DEBUG
void APIENTRY gl_debug_message_callback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);
#endif

#endif // !RENDERER_H

