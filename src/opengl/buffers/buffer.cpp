module wd.opengl.Buffer;

namespace WD::GL
{
    Buffer::Buffer()
        : mID(0)
        , mTarget(0)
    {
        glGenBuffers(1, &mID);
        if (mID == 0) throw glGetError();
    }

    GLuint Buffer::ID() const
    {
        return mID;
    }

    GLenum Buffer::Target() const
    {
        return mTarget;
    }

    bool Buffer::BindTo(const GLenum target)
    {
        glBindBuffer(target, mID);
        if(glGetError() != GL_NO_ERROR) return false;

        mTarget = target;
        return true;
    }

    bool Buffer::BufferData(const void* data, const size_t size, const GLenum usage)
    {
        glNamedBufferData(mID, size, data, usage);
        if(glGetError() != GL_NO_ERROR) return false;

        return true;
    }

    Buffer::~Buffer()
    {
        glDeleteBuffers(1, &mID);
    }
}
