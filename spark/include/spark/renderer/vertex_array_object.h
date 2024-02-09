#ifndef SPARK_ENGINE_VERTEX_ARRAY_OBJECT_H
#define SPARK_ENGINE_VERTEX_ARRAY_OBJECT_H
#include "spark/core/base.h"
#include "spark/renderer/opengl.h"

namespace Spark{
    class VertexArrayObject{
    private:
        GLRef m_id;
    public:
        VertexArrayObject();
        ~VertexArrayObject();
    };
}

#endif //SPARK_ENGINE_VERTEX_ARRAY_OBJECT_H
