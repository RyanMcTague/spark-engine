#ifndef SPARK_ENGINE_ASSET_MANAGER_H
#define SPARK_ENGINE_ASSET_MANAGER_H
#include "spark/core/base.h"
#include "spark/assets/sprite.h"
#include "spark/assets/tilemap.h"
namespace Spark{
    SPARK_API class AssetManager{
    private:
        AssetManager();
        static std::map<std::string, Sprite*> m_sprites;
        static std::map<std::string, Tilemap*> m_tilemaps;
    public:
        static void Destroy();

        static void RegisterSprite(const std::string& name, const std::string& path);
        static void RegisterSprite(const std::string& name, const std::string& path, const vec2& tilesize);
        static Sprite* GetSprite(const std::string& name);

        static void RegisterTilemap(const std::string& name, const std::string& path);
        static Tilemap* GetTilemap(const std::string& name);
    };
}

#endif //SPARK_ENGINE_ASSET_MANAGER_H
