module;

#include "wd/sdl/opengl/gl.h"

module wd.sdl.opengl.object.vertex.Array;

namespace wd::sdl::opengl::object::vertex
{
	Array::Array()
		: Object([]
				{
					GLuint id;
					glGenVertexArrays(1, &id);
					return id;
				}()
				, GL_VERTEX_ARRAY)
		, VBO(GL_ARRAY_BUFFER)
		, EBO(GL_ELEMENT_ARRAY_BUFFER)
	{
		glBindVertexArray(ID);
	}

	void Array::ReadVBO() noexcept
	{
		constexpr auto axes = 3;
		glVertexAttribPointer(
				0
				, axes
				, GL_DOUBLE
				, GL_FALSE
				, axes * sizeof(double)
				, nullptr);
	}

	void Array::Enable() noexcept
	{
		glEnableVertexArrayAttrib(ID, 0);
	}

	void Array::Disable() noexcept
	{
		glDisableVertexArrayAttrib(ID, 0);
	}
}
