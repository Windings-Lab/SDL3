module;

#include <vector>
#include <memory>

export module wd.sdl.opengl.object.Storage;

import wd.sdl.opengl.object.creator_node;
import wd.utility.Constructors;

export namespace wd::sdl::opengl::object
{
    using shader_container = std::vector<std::unique_ptr<Shader>>;
    using buffer_container = std::vector<std::unique_ptr<Buffer>>;
    namespace shader
    {
        using program_container = std::vector<std::unique_ptr<Program>>;
    }
    namespace vertex
    {
        using array_container = std::vector<std::unique_ptr<Array>>;
    }

    struct Storage : utility::NonMovable
    {
        shader::program_container Programs;
        shader_container Shaders;
        buffer_container Buffers;
        vertex::array_container VertexArrays;

    public:
        ~Storage();
    };
}
