#include "spark/core/base.h"
#include "spark/renderer/opengl.h"
const char* Spark::glGetErrorString(GLenum error)
{
    switch (error)
    {
        case GL_NO_ERROR:
            return "NO_ERROR";
        case GL_INVALID_ENUM:
            return "INVALID_ENUM Enum";
        case GL_INVALID_VALUE:
            return "INVALID_VALUE";
        case GL_INVALID_OPERATION:
            return "INVALID_OPERATION";
        case GL_INVALID_FRAMEBUFFER_OPERATION:
            return "INVALID_FRAMEBUFFER_OPERATION";
        case GL_OUT_OF_MEMORY:
            return "OUT_OF_MEMORY";
        case GL_STACK_UNDERFLOW:
            return "STACK_UNDERFLOW";
        case GL_STACK_OVERFLOW:
            return "STACK_OVERFLOW";
        default:
            return "UNKNOWN_ERROR";
    }
}

void Spark::__checkGLkError(const char *filename, int line){
    GLenum err;
    bool hasError = false;
    while ((err = glGetError()) != GL_NO_ERROR)
    {
        Logger::Error("OPENGL::" + std::string(glGetErrorString(err))
                      + " in " + std::string(filename) + " (" + std::to_string(line) + ")");
        hasError = true;
    }

    if (hasError){
        assert(false);
    }
}
