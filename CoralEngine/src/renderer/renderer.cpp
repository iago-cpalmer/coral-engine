#include "renderer.h"
#include <string>
#include <glm/trigonometric.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include "data/mesh.h"

//static RenderData _RenderData;
RenderData RendererData{};

void renderer_init_opengl()
{

#ifdef WIREFRAME_MODE
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
#endif // WIREFRAME_MODE

#if _DEBUG
	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(gl_debug_message_callback, NULL);
#endif

	glEnable(GL_DEPTH_TEST);

	window_set_viewport_change_callback(renderer_change_viewport_callback);
}


void renderer_set_clear_color_normalized(float r, float g, float b)
{
	glClearColor(r, g, b, 1.0f);
}

void renderer_set_clear_color(float r, float g, float b)
{
	glClearColor(r / 256.0f, g / 256.0f, b / 256.0f, 1.0f);
}


void renderer_change_viewport_callback(int rWidth, int rHeight)
{
	glViewport(0, 0, rWidth, rHeight);
	RendererData.ViewportSizePx = glm::vec2(rWidth, rHeight);
}

void renderer_prepare_frame()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void renderer_finish_render()
{
	// handle events & swap buffer
	glfwSwapBuffers(get_window_ptr());
	glfwPollEvents();
}

void draw_indexed(unsigned int vao, unsigned int ebo, unsigned int indexNr)
{
	glBindVertexArray(vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glDrawElements(GL_TRIANGLES, indexNr, GL_UNSIGNED_INT, 0);
}

#if _DEBUG
static void APIENTRY gl_debug_message_callback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
	std::string _source;
	std::string _type;
	std::string _severity;

	switch (source) {
	case GL_DEBUG_SOURCE_API:
		_source = "API";
		break;

	case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
		_source = "WINDOW SYSTEM";
		break;

	case GL_DEBUG_SOURCE_SHADER_COMPILER:
		_source = "SHADER COMPILER";
		break;

	case GL_DEBUG_SOURCE_THIRD_PARTY:
		_source = "THIRD PARTY";
		break;

	case GL_DEBUG_SOURCE_APPLICATION:
		_source = "APPLICATION";
		break;

	case GL_DEBUG_SOURCE_OTHER:
		_source = "UNKNOWN";
		break;

	default:
		_source = "UNKNOWN";
		break;
	}

	switch (type) {
	case GL_DEBUG_TYPE_ERROR:
		_type = "ERROR";
		break;

	case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
		_type = "DEPRECATED BEHAVIOR";
		break;

	case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
		_type = "UDEFINED BEHAVIOR";
		break;

	case GL_DEBUG_TYPE_PORTABILITY:
		_type = "PORTABILITY";
		break;

	case GL_DEBUG_TYPE_PERFORMANCE:
		_type = "PERFORMANCE";
		break;

	case GL_DEBUG_TYPE_OTHER:
		_type = "OTHER";
		break;

	case GL_DEBUG_TYPE_MARKER:
		_type = "MARKER";
		break;

	default:
		_type = "UNKNOWN";
		break;
	}

	switch (severity) {
	case GL_DEBUG_SEVERITY_HIGH:
		_severity = "HIGH";
#ifndef DEBUG_HIGH_SEVERITY
		return;
#endif // DEBUG_HIGH_SEVERITY

		break;

	case GL_DEBUG_SEVERITY_MEDIUM:
		_severity = "MEDIUM";
#ifndef DEBUG_MEDIUM_SEVERITY
		return;
#endif // DEBUG_MEDIUM_SEVERITY
		break;

	case GL_DEBUG_SEVERITY_LOW:
		_severity = "LOW";
#ifndef DEBUG_LOW_SEVERITY
		return;
#endif // DEBUG_LOW_SEVERITY
		break;

	case GL_DEBUG_SEVERITY_NOTIFICATION:
		_severity = "NOTIFICATION";
#ifndef DEBUG_NOTIFICATION_SEVERITY
		return;
#endif // DEBUG_NOTIFICATION_SEVERITY
		break;

	default:
		_severity = "UNKNOWN";
		break;
	}



	printf("%d: %s of %s severity, raised from %s: %s\n",
		id, _type.c_str(), _severity.c_str(), _source.c_str(), message);
}
#endif