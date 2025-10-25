#include "render_buffer.h"

RenderBuffer create_rb(GLenum format, int width, int height)
{
	RenderBuffer rb = { 0 };
	rb.Format = format;
	glGenRenderbuffers(1, &rb.Id);
	glBindRenderbuffer(GL_RENDERBUFFER, rb.Id);
	glRenderbufferStorage(GL_RENDERBUFFER, format, width, height);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);

	return rb;
}