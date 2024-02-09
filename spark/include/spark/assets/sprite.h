#ifndef SPARK_ENGINE_SPRITE_H
#define SPARK_ENGINE_SPRITE_H
#include "spark/core/base.h"
#include "spark/core/asset.h"
#include "spark/renderer/texture_2d.h"

namespace Spark{
    SPARK_API class Sprite{
    private:
        Texture2D* m_texture;
        vec2 m_tileSize{};
        bool m_isSpriteSheet;
    public:
        explicit Sprite(const std::string& path);
        explicit Sprite(const std::string& path, const vec2& tileSize);
        ~Sprite();

        Texture2D* GetTexture();
        const vec2& GetTileSize();
        bool IsSpiteSheet();
    };
}

#endif //SPARK_ENGINE_SPRITE_H
