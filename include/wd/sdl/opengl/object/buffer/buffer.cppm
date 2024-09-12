module;

#include <span>
#include <SDL3/SDL_assert.h>
#include "wd/sdl/opengl/gl.h"

export module wd.sdl.opengl.object.Buffer;

import wd.sdl.opengl.object.Object;

template <typename T>
concept DataType = requires
{
    std::same_as<const T, GLfloat>
    || std::same_as<const T, GLdouble>
    || std::same_as<const T, GLuint>;
};

export namespace wd::sdl::opengl::object
{
    struct Buffer : public Object
    {
        template<DataType T>
        void BufferData(std::span<T> data, GLenum usage);
        void Bind();
        void Unbind();

        Buffer() = delete;
        explicit Buffer(GLenum type);
        virtual ~Buffer() override;
    };

    template <DataType T>
    void Buffer::BufferData(std::span<T> data, const GLenum usage)
    {
        glNamedBufferData(ID, data.size_bytes(), data.data(), usage);
        SDL_assert(!glGetError());
    }
}
