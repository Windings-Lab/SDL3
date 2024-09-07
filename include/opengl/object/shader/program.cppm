module;

#include <boost/mpl/set/aux_/has_key_impl.hpp>
#include "opengl/gl.h"

export module wd.gl.object.shader.Program;

import wd.gl.object.shader.Container;
import wd.gl.object.Object;

export namespace wd::gl::object::shader
{
    class Program : public Object
    {
    public:
        void Use() const noexcept;
        void Attach(const Shader* shader);
        auto DetachBy(GLuint id) -> const Shader*;
        auto DetachBy(const GLchar* path) -> const Shader*;

    public:
        Program();
        virtual ~Program() override;

    private:
        auto Detach(const Shader& shader) -> void;
        shader_container_ptr mShaders;
    };
}
