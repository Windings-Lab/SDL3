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

	void Program::Attach(const std::weak_ptr<Shader>& shader)
	{
		if(shader.expired()) return;

		auto shaderPtr = shader.lock();
		glAttachShader(ID, shaderPtr->ID);
		SDL_assert(!glGetError());

		mShaders.emplace_back(std::move(shaderPtr));
	}

	auto Program::DetachBy(GLuint id) -> shader_ptr
	{
		auto pte = std::ranges::find(mShaders, id, &Shader::ID);
		SDL_assert(pte != mShaders.end());

		const auto shader = *pte;

		std::ranges::rotate(pte, pte + 1, mShaders.end());
		mShaders.pop_back();
		glDetachShader(ID, shader->ID);
		SDL_assert(!glGetError());

		return shader;
	}
}
