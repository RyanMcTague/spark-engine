#ifndef SPARK_ENGINE_OPENGL_H
#define SPARK_ENGINE_OPENGL_H
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "spark/core/platform.h"

namespace Spark{
    SPARK_API using GLRef = unsigned int;
    SPARK_API const GLRef GlNullRef = 0;

    const char* glGetErrorString(GLenum error);

    void __checkGLkError(const char *filename, int line);
}

#define glCheck(x) \
    x; \
    Spark::__checkGLkError(__FILE__, __LINE__)

#endif //SPARK_ENGINE_OPENGL_H
