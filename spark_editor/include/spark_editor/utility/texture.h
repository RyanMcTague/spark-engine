#ifndef SPARK_ENGINE_TEXTURE_H
#define SPARK_ENGINE_TEXTURE_H
#include "spark_editor/base.h"

namespace Textures{
    struct TextureInfo{
        uint32_t ref = 0;
        int width = 0;
        int height = 0;
        GLenum format = GL_NONE;
    };
    TextureInfo Create(const std::string& path);
    uint32_t CreateGrid(int width, int height, const ImVec2& gridSize, uint32_t color = 0x55FFFFFF);
}
enum TextureWrap{
    Repeat = GL_REPEAT
};

enum TextureFilter{
    Nearest = GL_NEAREST,
    Linear = GL_LINEAR
};

enum TextureFormat{
    RGBA = GL_RGBA,
};

class Texture{
private:
    uint32_t m_id;
    int m_width, m_height;
    ImVec2 m_size{};
    TextureWrap m_wrapS, m_wrapT;
    TextureFilter m_minFilter, m_magFilter;
    TextureFormat m_internalFormat, m_targetFormat;
public:
    Texture();
    ~Texture();

    void SetWrap(TextureWrap x, TextureWrap y);
    void SetFormat(TextureFormat internal, TextureFormat target);
    void SetFilter(TextureFilter min, TextureFilter mag);
    void Load(int width, int height, uint8_t* data);
    void Update(int width, int height, uint8_t* data);
    [[nodiscard]] const ImVec2& GetSize() const;
    [[nodiscard]] uint32_t GetID() const;
};
#endif //SPARK_ENGINE_TEXTURE_H
