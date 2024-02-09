#ifndef SPARK_ENGINE_SPRITE_H
#define SPARK_ENGINE_SPRITE_H
#include "spark_editor/base.h"

struct Tile{
    ImVec2 uv0;
    ImVec2 uv1;
    int x;
    int y;
    Tile(const ImVec2& uv0, const ImVec2& uv1, int x, int y);
};


struct Sprite{
    Point       spriteSize{};
    uint32_t    texture;
    std::string path;
    std::string name;
    Point       tileSize{};
    Point       tileCount{};
    std::vector<Tile> tiles;
    bool  isMultiple;
    explicit Sprite(const std::string& path);
    void Split(const Point& size);
    ~Sprite();
};

using OnTileClicked = std::function<void(const Tile&)>;



#endif //SPARK_ENGINE_SPRITE_H
