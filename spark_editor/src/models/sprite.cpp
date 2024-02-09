#include "spark_editor/models/sprite.h"
#include "spark_editor/utility/texture.h"
#include "spark_editor/utility/file_system.h"
Tile::Tile(const ImVec2 &uv0, const ImVec2 &uv1, int x, int y) {
    this->uv0 = uv0;
    this->uv1 = uv1;
    this->x = x;
    this->y = y;
}

Sprite::Sprite(const std::string& path){
    auto info = Textures::Create(path);
    this->path = path;
    this->name = FileSystem::GetFileNameFromPath(path);
    this->texture = info.ref;
    this->spriteSize = { info.width, info.height };
    this->tileSize = spriteSize;
    this->isMultiple = false;
    this->tileCount = { 1, 1 };
    this->tiles.emplace_back(Tile(ImVec2{0, 0}, {(float )info.width, (float )info.height}, 0, 0));
}

Sprite::~Sprite(){
    if(texture != 0)
        glDeleteTextures(1, &texture);
}
void Sprite::Split(const Point& size){
    this->tileSize = size;
    tileCount.x = (int)(this->spriteSize.x / this->tileSize.x);
    tileCount.y = (int)(this->spriteSize.y / this->tileSize.y);
    tiles.clear();
    for (int y = 0; y < tileCount.y; y++) {
        for (int x = 0; x < tileCount.x; x++) {
            ImVec2 start = ImVec2((float)x * (float)tileSize.x, (float )y * (float)tileSize.y);
            ImVec2 uv0 = ImVec2(start.x / (float)spriteSize.x, start.y / (float)spriteSize.y);
            ImVec2 uv1 = ImVec2((start.x + (float)tileSize.x) / (float)spriteSize.x,
                                (start.y + (float)tileSize.y) / (float)spriteSize.y);
            tiles.emplace_back(uv0, uv1, x, y);
        }
    }
}

