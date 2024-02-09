#include "spark/renderer/texture_2d.h"

Spark::Texture2D::Texture2D() {
    m_id = 0;
    m_width = 0;
    m_height = 0;
    m_wrapS = TextureWrap::Repeat;
    m_wrapT = TextureWrap::Repeat;
    m_minFilter = TextureFilter::Linear;
    m_magFilter = TextureFilter::Linear;
    m_internalFormat = TextureFormat::RGBA;
    m_targetFormat = TextureFormat::RGBA;
}

Spark::Texture2D::~Texture2D(){
    glDeleteTextures(1, &m_id);
}

void Spark::Texture2D::SetWrap(TextureWrap x, TextureWrap y){
    m_wrapS = x;
    m_wrapT = y;
}
void Spark::Texture2D::SetFormat(TextureFormat internal, TextureFormat target){
    m_internalFormat = internal;
    m_targetFormat = target;
}
void Spark::Texture2D::SetFilter(TextureFilter min, TextureFilter mag){
    m_magFilter = mag;
    m_minFilter = min;
}

const Spark::vec2& Spark::Texture2D::GetSize() const{
    return m_size;
}

void Spark::Texture2D::Load(int width, int height, uint8_t* data){
    m_width = width;
    m_height = height;
    m_size = {m_width, m_height};
    glGenTextures(1, &m_id);
    glBindTexture(GL_TEXTURE_2D, m_id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, (GLint)m_wrapS);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, (GLint)m_wrapT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, (GLint)m_minFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, (GLint)m_magFilter);
    glTexImage2D(GL_TEXTURE_2D, 0, m_internalFormat, m_width, m_height, 0, m_targetFormat, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
}

void Spark::Texture2D::Bind() const {
    glBindTexture(GL_TEXTURE_2D, m_id);
}
