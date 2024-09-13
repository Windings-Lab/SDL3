module;

#include <vector>
#include "wd/sdl/opengl/gl.h"

export module wd.sdl.opengl.object.shader.Program;

import wd.sdl.opengl.object.Object;
import wd.sdl.opengl.object.shader.Shader;

export namespace wd::sdl::opengl::object::shader
{
	using shader_container_ptr = std::vector<Shader*>;

	class Program : public Object
	{
	public:
		void Use() const noexcept;
		void Link() const noexcept;
		void Attach(Shader* shader);
		auto DetachBy(GLuint id) -> Shader*;

	public:
		Program();
		virtual ~Program() override;

	private:
		shader_container_ptr mShaders;
	};
}
