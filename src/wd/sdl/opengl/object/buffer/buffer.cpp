module;

#include <SDL3/SDL_assert.h>
#include "wd/sdl/opengl/gl.h"

module wd.sdl.opengl.object.Buffer;

namespace wd::sdl::opengl::object
{
    Buffer::Buffer(const GLenum type) : Object([]
    {
        GLuint id;
        glGenBuffers(1, &id);
        return id;
    }(), type)
    {
    }

    void Buffer::BufferData(const void* data, const size_t size, const GLenum usage)
    {
        glNamedBufferData(ID, size, data, usage);
        SDL_assert(!glGetError());
    }

    void Buffer::Bind()
    {
        glBindBuffer(mType, ID);
        SDL_assert(!glGetError());
    }

    void Buffer::Unbind()
    {
        glBindBuffer(mType, 0);
        SDL_assert(!glGetError());
    }

    Buffer::~Buffer()
    {
        glDeleteBuffers(1, &ID);
    }
}
