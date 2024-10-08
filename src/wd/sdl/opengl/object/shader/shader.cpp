module;

#include <format>
#include <SDL3/SDL_filesystem.h>
#include <SDL3/SDL_iostream.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_assert.h>

#include "wd/sdl/opengl/gl.h"

module wd.sdl.opengl.object.shader.Shader;

namespace
{
	bool CompileSuccess(const wd::sdl::opengl::object::Shader& shader)
	{
		// Check for successful compilation
		int success;
		glGetShaderiv(shader.ID, GL_COMPILE_STATUS, &success);
		if(!success)
		{
			constexpr int bufSize = 512;
			char infoLog[bufSize];
			glGetShaderInfoLog(shader.ID, bufSize, nullptr, infoLog);
			auto log = std::format(
					"Shader compilation failed:\n" "Info: %s\n", infoLog
					, "Path: %s\n", shader.Path
					, "Type: %s", shader.Type());
			SDL_LogDebug(SDL_LOG_PRIORITY_DEBUG, "%s", log.c_str());
		}

		return success;
	}
}

namespace wd::sdl::opengl::object
{
	Shader::Shader(const GLchar* path, const GLenum type)
		: Object(glCreateShader(type), type)
		, Path(path)
	{
	}

	void Shader::Compile()
	{
		SDL_assert(SDL_GetPathInfo(Path, nullptr));

		auto data = SDL_LoadFile(Path, nullptr);
		auto code = static_cast<const char*>(data);
		glShaderSource(ID, 1, &code, nullptr);
		glCompileShader(ID);

		SDL_assert(CompileSuccess(*this));
		SDL_free(data); // TODO: make RAII if needed
	}

	Shader::~Shader()
	{
		glDeleteShader(ID);
	}
}
