module;

#include <vector>
#include <memory>
#include "wd/sdl/opengl/gl.h"

export module wd.sdl.opengl.object.shader.Program;

import wd.sdl.opengl.object.Object;
import wd.sdl.opengl.object.shader.Shader;

export namespace wd::sdl::opengl::object::shader
{
	using shader_ptr = std::shared_ptr<Shader>;
	using shader_container = std::vector<shader_ptr>;

	class Program : public Object
	{
	public:
		void Use() const noexcept;
		void Link() const noexcept;
		void Attach(const std::weak_ptr<Shader>& shader);
		auto DetachBy(GLuint id) -> shader_ptr;

	public:
		Program();
		virtual ~Program() override;

	private:
		shader_container mShaders;
	};
}
