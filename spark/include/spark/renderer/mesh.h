#ifndef SPARK_ENGINE_MESH_H
#define SPARK_ENGINE_MESH_H
#include "spark/core/base.h"
#include "spark/renderer/opengl.h"

namespace Spark{
    SPARK_API class Mesh{
    private:
        GLRef m_vao;
        GLRef m_vbo;
        GLRef m_ebo;
        mat4 m_mvp{};
    public:
        Mesh();
        ~Mesh();
        void Build();
        void Render() const;
    };
}


#endif //SPARK_ENGINE_MESH_H
