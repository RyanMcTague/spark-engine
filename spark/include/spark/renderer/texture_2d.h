#ifndef SPARK_ENGINE_TEXTURE_2D_H
#define SPARK_ENGINE_TEXTURE_2D_H
#include "spark/core/base.h"
#include "spark/renderer/opengl.h"

namespace Spark{

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

    SPARK_API class Texture2D{
    private:
        GLRef m_id;
        int m_width, m_height;
        vec2 m_size{};
        TextureWrap m_wrapS, m_wrapT;
        TextureFilter m_minFilter, m_magFilter;
        TextureFormat m_internalFormat, m_targetFormat;
    public:
        Texture2D();
        ~Texture2D();

        void SetWrap(TextureWrap x, TextureWrap y);
        void SetFormat(TextureFormat internal, TextureFormat target);
        void SetFilter(TextureFilter min, TextureFilter mag);
        void Load(int width, int height, uint8_t* data);
        [[nodiscard]] const vec2& GetSize() const;
        void Bind() const;
    };
}

#endif //SPARK_ENGINE_TEXTURE_2D_H
