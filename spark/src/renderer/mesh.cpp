#include "spark/renderer/mesh.h"
#include "spark/renderer/shader.h"


float square[] = {
         0.5f, 0.5f, 0.0f, 1.0f, 1.0f,   // top right
         0.5f, -0.5f, 0.0f,  1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,  0.0f, 0.0f, // bottom left
        -0.5f, 0.5f, 0.0f,  0.0f, 1.0f,  // top left
};

uint32_t indices[] = {
        0, 1, 3,
        1, 2, 3
};

Spark::Mesh::Mesh() {
    m_vao = GlNullRef;
    m_vbo = GlNullRef;
}


Spark::Mesh::~Mesh(){
    if(m_ebo != GlNullRef){
        glDeleteBuffers(1, &m_vbo);
    }

    if(m_vbo != GlNullRef){
        glDeleteBuffers(1, &m_ebo);
    }

    if(m_vao != GlNullRef){
        glDeleteVertexArrays(1, &m_vbo);
    }
}

void Spark::Mesh::Build() {
    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vbo);
    glGenBuffers(1, &m_ebo);

    glBindVertexArray(m_vao);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, 20 * sizeof(float), square, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(uint32_t), indices, GL_STATIC_DRAW);


    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float ), nullptr);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float ), (void*)(3 * sizeof(float )));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}


void Spark::Mesh::Render() const{
    glBindVertexArray(m_vao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
}