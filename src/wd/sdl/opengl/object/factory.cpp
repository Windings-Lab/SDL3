module;

#include <memory>
#include "wd/sdl/opengl/gl.h"

module wd.sdl.opengl.object.Factory;

namespace wd::sdl::opengl::object
{
	auto Factory::GetStorage() const noexcept -> const Storage&
	{
		return mStorage;
	}

	auto Factory::CreateShader(const GLchar* path, const GLenum type) noexcept -> std::weak_ptr<Shader>
	{
		auto shader = std::make_shared<Shader>(path, type);
		shader->Compile();
		std::weak_ptr shaderPtr = shader;
		mStorage.Shaders.emplace_back(std::move(shader));

		return shaderPtr;
	}

	auto Factory::CreateProgram() noexcept -> shader::Program&
	{
		auto program          = std::make_unique<shader::Program>();
		const auto programPtr = program.get();
		mStorage.Programs.emplace_back(std::move(program));

		return *programPtr;
	}

	auto Factory::CreateBuffer(GLenum type) noexcept -> Buffer&
	{
		auto buffer          = std::make_unique<Buffer>(type);
		const auto bufferPtr = buffer.get();
		mStorage.Buffers.emplace_back(std::move(buffer));

		return *bufferPtr;
	}

	auto Factory::CreateVertexArray() noexcept -> vertex::Array&
	{
		auto vertexArray          = std::make_unique<vertex::Array>();
		const auto vertexArrayPtr = vertexArray.get();
		mStorage.VertexArrays.emplace_back(std::move(vertexArray));

		return *vertexArrayPtr;
	}
}
