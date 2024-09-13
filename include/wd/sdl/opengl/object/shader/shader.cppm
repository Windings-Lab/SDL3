module;

#include "wd/sdl/opengl/gl.h"

export module wd.sdl.opengl.object.shader.Shader;

import wd.sdl.opengl.object.Object;

export namespace wd::sdl::opengl::object
{
	struct Shader : public Object
	{
		const GLchar* const Path;

		void Compile();

		Shader() = delete;
		Shader(const GLchar* path, GLenum type);
		virtual ~Shader() override;
	};
}
