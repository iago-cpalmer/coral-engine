#include "frame_buffer.h"
#include "../../../core/ErrorHandler.h"


FrameBuffer create_fb(const Texture* p_texture)
{
	unsigned int fbo;
	glGenFramebuffers(1, &fbo);
	FrameBuffer fb = FrameBuffer{ fbo };
	
	use_fb(fb);
	unsigned int rbo;
	
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, p_texture->Texture, 0);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		THROW_ERROR("ERROR::create_fb - Frame buffer was not created correctly");
	}

	fb_unbind(fb);

	return fb;
}

void fb_attach_rb(FrameBuffer* fb, RenderBuffer* rb)
{
	use_fb(*fb);
	switch (rb->Format)
	{
		case GL_DEPTH:
			glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rb->Id);
			break;
		case GL_DEPTH24_STENCIL8:
		case GL_DEPTH32F_STENCIL8:
			glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rb->Id);
			break;
		default:
			THROW_ERROR("ERROR::fb_attach_rb - Not supported format of render buffer object");
	}
	fb_unbind(*fb);
}

void release_fb(FrameBuffer& r_fb)
{
	glDeleteFramebuffers(1, &r_fb.Id);
}
