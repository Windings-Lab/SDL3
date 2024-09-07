module;

#include <vector>
#include "opengl/gl.h"

export module wd.gl.object.shader.Program;

import wd.gl.object.Object;

namespace wd::gl::object
{
    using shader_container_ptr = std::vector<struct Shader*>;
}

export namespace wd::gl::object::shader
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
