module;

#include "opengl/glad/gl.h"
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/hashed_index.hpp>

export module wd.gl.shader.Container;

export import wd.gl.shader.Shader;

export using boost::multi_index::multi_index_container;
export using boost::multi_index::indexed_by;
export using boost::multi_index::hashed_unique;

export
{
    using shader_container_ptr = multi_index_container
    <
        const wd::gl::Shader*,
        indexed_by
        <
            hashed_unique<BOOST_MULTI_INDEX_MEMBER(wd::gl::Shader, const GLuint, ID)>,
            hashed_unique<BOOST_MULTI_INDEX_MEMBER(wd::gl::Shader, const GLchar* const, Path)>
        >
    >;

    using shader_container = multi_index_container
    <
        std::unique_ptr<wd::gl::Shader>,
        indexed_by
        <
            hashed_unique<BOOST_MULTI_INDEX_MEMBER(wd::gl::Shader, const GLuint, ID)>,
            hashed_unique<BOOST_MULTI_INDEX_MEMBER(wd::gl::Shader, const GLchar* const, Path)>
        >
    >;
}
