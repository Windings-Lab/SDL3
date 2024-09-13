module;

#include <SDL3/SDL_assert.h>

#include "wd/sdl/opengl/gl.h"

module wd.sdl.opengl.object.Object;

namespace wd::sdl::opengl
{
	Object::~Object()
	{
	}

	GLenum Object::Type() const noexcept
	{
		return mType;
	}

	Object::Object(const GLuint id, const GLenum type)
		: ID(id)
		, mType(type)
	{
		SDL_assert(!(glGetError() || ID == 0));
	}
}
