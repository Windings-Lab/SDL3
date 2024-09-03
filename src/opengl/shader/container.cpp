module wd.opengl.shader.Container;

import wd.opengl.shader.Shader;

namespace boost::multi_index
{
    auto extractID(const WD::GL::Shader& shader) -> GLuint
    {
        return shader.ID;
    }

    auto extractPath(const WD::GL::Shader& shader) -> const GLchar*
    {
        return shader.Path;
    }
}
