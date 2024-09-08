module;

#include <vector>
#include "wd/sdl/opengl/gl.h"

export module wd.sdl.opengl.object.shader.Program;

import wd.sdl.opengl.object.Object;

namespace wd::sdl::opengl::object
{
    using shader_container_ptr = std::vector<struct Shader*>;
}

export namespace wd::sdl::opengl::object::shader
{
    class Program : public Object
    {
    public:
        void Use() const noexcept;
        void Attach(Shader* shader);
        auto DetachBy(GLuint id) -> Shader*;

    public:
        Program();
        virtual ~Program() override;

    private:
        auto Detach(const Shader& shader) -> void;
        shader_container_ptr mShaders;
    };
}
