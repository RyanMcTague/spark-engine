#ifndef SPARK_ENGINE_PROJECT_H
#define SPARK_ENGINE_PROJECT_H
#include "spark_editor/base.h"
#include "spark_editor/models/sprite.h"
#include "spark_editor/models/tile_map.h"

class Project{
private:
    static Project* m_instance;
    std::string m_basePath;
    std::string m_name;
    std::map<std::string, Sprite*>  m_sprites;
    std::map<std::string, TileMap*> m_tileMaps;
    Project(const std::string& path, bool isNew);

public:
    ~Project();

    static Project* Get();
    static void Destroy();
    static Project* Create(const std::string& path);
    static Project* Open(const std::string& path);

    const std::string& GetBasePath();
    const std::string& GetName();

    Sprite* AddSprite(const std::string& path);
    Sprite* GetSprite(const std::string& path);

    TileMap* AddTileMap(const std::string& path);
    TileMap* GetTileMap(const std::string& path);
};

#endif //SPARK_ENGINE_PROJECT_H
