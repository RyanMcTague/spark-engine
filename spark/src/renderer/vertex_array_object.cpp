#include "spark/renderer/vertex_array_object.h"

Spark::VertexArrayObject::VertexArrayObject(){
    m_id = 0;
    glGenVertexArrays(1, &m_id);
}

Spark::VertexArrayObject::~VertexArrayObject() {
    if (m_id != 0)
        glDeleteVertexArrays(1, &m_id);
}