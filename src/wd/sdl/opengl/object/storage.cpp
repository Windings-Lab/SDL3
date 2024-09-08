module wd.sdl.opengl.object.Storage;

namespace wd::sdl::opengl::object
{
    Storage::~Storage()
    {
        Programs.clear();
        Shaders.clear();
        Buffers.clear();
        VertexArrays.clear();
    }
}
