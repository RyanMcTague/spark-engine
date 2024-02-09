#ifndef SPARK_ENGINE_TILE_MAP_H
#define SPARK_ENGINE_TILE_MAP_H
#include "spark_editor/base.h"
#include "spark_editor/models/sprite.h"

class TileMap;

struct TileMapLayer{
    TileMap* tileMap;
    Sprite* sprite;
    bool visible = true;
    std::vector<uint32_t> tiles;
    TileMapLayer(Sprite* tileSheet, TileMap* tileMap);
};

using LayerList = std::vector<TileMapLayer>;

struct TileMap{
    Point       tileCount{};
    LayerList   layers;
    std::string path;

    explicit TileMap(const std::string& path);
    ~TileMap();

    [[nodiscard]] const Tile& GetTile(int layer, const Point& position) const;
    void SetTile(int layer, const Point& tile, const Point& position);
    int AddLayer(Sprite* tileSheet);
};

#endif //SPARK_ENGINE_TILE_MAP_H
