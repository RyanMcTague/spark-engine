#include "spark_editor/utility/texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Textures::TextureInfo Textures::Create(const std::string& path) {
    int width, height, nrChannels;
    uint32_t texture;
    uint8_t* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
    if (data) {
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(data);
    }else{
        spdlog::error("Failed to load texture");
        return {};
    }
    return { texture, width, height, nrChannels == 4 ? (GLenum)GL_RGBA : (GLenum)GL_RGB };
}

uint32_t Textures::CreateGrid(int width, int height, const ImVec2& gridSize, uint32_t color){
    int gridX = (int)gridSize.x;
    int gridY = (int)gridSize.y;
    uint32_t texture;

    auto* gridData = new uint32_t[width * height];
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            uint32_t index = y * width + x;
            if ((y % gridY == 0 || x % gridX == 0) && (y != 0 && x != 0))
                gridData[index] = color;
            else
                gridData[index] = 0;
        }
    }

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, gridData);
    glGenerateMipmap(GL_TEXTURE_2D);
    delete[] gridData;
    return texture;
}

Texture::Texture() {
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

Texture::~Texture(){
    glDeleteTextures(1, &m_id);
}

void Texture::SetWrap(TextureWrap x, TextureWrap y){
    m_wrapS = x;
    m_wrapT = y;
}
void Texture::SetFormat(TextureFormat internal, TextureFormat target){
    m_internalFormat = internal;
    m_targetFormat = target;
}
void Texture::SetFilter(TextureFilter min, TextureFilter mag){
    m_magFilter = mag;
    m_minFilter = min;
}

const ImVec2& Texture::GetSize() const{
    return m_size;
}

uint32_t Texture::GetID() const{
    return m_id;
}

void Texture::Load(int width, int height, uint8_t* data){
    m_width = width;
    m_height = height;
    m_size = {(float )m_width, (float )m_height};
    glGenTextures(1, &m_id);
    glBindTexture(GL_TEXTURE_2D, m_id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, (GLint)m_wrapS);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, (GLint)m_wrapT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, (GLint)m_minFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, (GLint)m_magFilter);
    glTexImage2D(GL_TEXTURE_2D, 0, m_internalFormat, m_width, m_height, 0, m_targetFormat, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
}



void Texture::Update(int width, int height, uint8_t* data){
    m_width = width;
    m_height = height;
    m_size = {(float )m_width, (float )m_height};
    glBindTexture(GL_TEXTURE_2D, m_id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, (GLint)m_wrapS);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, (GLint)m_wrapT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, (GLint)m_minFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, (GLint)m_magFilter);
    glTexImage2D(GL_TEXTURE_2D, 0, m_internalFormat, m_width, m_height, 0, m_targetFormat, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
}