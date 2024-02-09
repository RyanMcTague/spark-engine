#include "spark_editor/models/tile_map.h"

TileMapLayer::TileMapLayer(Sprite* tileSheet, TileMap* tileMap){
    this->sprite = tileSheet;
    this->tileMap = tileMap;
    visible = true;
}


TileMap::TileMap(const std::string& path) {
    this->path = path;
}

TileMap::~TileMap() = default;

const Tile& TileMap::GetTile(int layer, const Point& position) const {
    auto* tileSheet = layers[layer].sprite;
    auto& tiles = layers[layer].tiles;
    return tileSheet->tiles[tiles[position.y * tileCount.x + position.x]];
}

void TileMap::SetTile(int layer, const Point& tile, const Point& position){
    auto* tileSheet = layers[layer].sprite;
    auto& tiles = layers[layer].tiles;
    tiles[position.y * tileCount.x + position.x] = tile.y * tileSheet->tileCount.x + tile.x;
}


int TileMap::AddLayer(Sprite* tileSheet){
    int id = (int)layers.size();
    layers.emplace_back(tileSheet, this);
    for (int i = 0; i < tileCount.x * tileCount.y; i++)
        layers[id].tiles.emplace_back(0);
    return id;
}
