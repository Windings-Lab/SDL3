module;

#include <SDL3/SDL_assert.h>
#include <vector>
#include <algorithm>
#include "wd/sdl/opengl/gl.h"

module wd.sdl.opengl.object.shader.Program;

namespace wd::sdl::opengl::object::shader
{
	Program::Program()
		: Object(glCreateProgram(), GL_PROGRAM)
	{
	}

	Program::~Program()
	{
		if(ID == 0) return;

		glDeleteProgram(ID);

		SDL_assert(!glGetError());
	}

	void Program::Use() const noexcept
	{
		glUseProgram(ID);
	}

	void Program::Link() const noexcept
	{
		glLinkProgram(ID);
	}

	void Program::Attach(Shader* shader)
	{
		if(!shader) return;

		glAttachShader(ID, shader->ID);
		SDL_assert(!glGetError());

		mShaders.emplace_back(shader);
	}

	auto Program::DetachBy(GLuint id) -> Shader*
	{
		const auto pte = std::ranges::find(mShaders, id, &Shader::ID);
		SDL_assert(pte != mShaders.end());

		const auto shader = *pte;

		std::erase(mShaders, shader);
		glDetachShader(ID, shader->ID);
		SDL_assert(!glGetError());

		return shader;
	}
}
