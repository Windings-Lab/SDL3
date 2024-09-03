module;

#include "opengl/glad/gl.h"
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/global_fun.hpp>
#include <boost/multi_index/hashed_index.hpp>

export module wd.opengl.shader.Container;

export namespace WD::GL
{
    class Shader;
}

export namespace boost::multi_index
{
    auto extractID(const WD::GL::Shader& shader) -> GLuint;
    auto extractPath(const WD::GL::Shader& shader) -> const GLchar*;

    using shader_container_ptr = multi_index_container
    <
        const WD::GL::Shader*,
        indexed_by
        <
            hashed_unique<global_fun<const WD::GL::Shader&, GLuint, &extractID>>,
            hashed_unique<global_fun<const WD::GL::Shader&, const GLchar*, &extractPath>>
        >
    >;

    using shader_container = multi_index_container
    <
        std::unique_ptr<WD::GL::Shader>,
        indexed_by
        <
            hashed_unique<global_fun<const WD::GL::Shader&, GLuint, &extractID>>,
            hashed_unique<global_fun<const WD::GL::Shader&, const GLchar*, &extractPath>>
        >
    >;
}
