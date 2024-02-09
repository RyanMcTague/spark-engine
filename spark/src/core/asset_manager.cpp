#include "spark/core/asset_manager.h"

std::map<std::string, Spark::Sprite*>  Spark::AssetManager::m_sprites;
std::map<std::string, Spark::Tilemap*> Spark::AssetManager::m_tilemaps;

Spark::AssetManager::AssetManager() = default;

void Spark::AssetManager::Destroy(){
    for(auto& el: m_sprites){
        delete el.second;
    }
    m_sprites.clear();
}

void Spark::AssetManager::RegisterSprite(const std::string& name, const std::string& path){
    auto it = m_sprites.find(name);
    if (it != m_sprites.end()){
        Logger::Warn("Sprite \"" + name + "\" already is registered!");
        return;
    }

    auto* sprite = new Sprite(path);
    m_sprites.emplace(name, sprite);
}

void Spark::AssetManager::RegisterSprite(const std::string& name, const std::string& path, const vec2& tilesize){
    auto it = m_sprites.find(name);
    if (it != m_sprites.end()){
        Logger::Warn("Sprite \"" + name + "\" already is registered!");
        return;
    }

    auto* sprite = new Sprite(path, tilesize);
    m_sprites.emplace(name, sprite);
}

Spark::Sprite* Spark::AssetManager::GetSprite(const std::string& name){
    auto it = m_sprites.find(name);
    if(it == m_sprites.end())
        return nullptr;

    return it->second;
}
void Spark::AssetManager::RegisterTilemap(const std::string& name, const std::string& path){
    auto it = m_tilemaps.find(name);
    if (it != m_tilemaps.end()){
        Logger::Warn("Tilemap \"" + name + "\" already is registered!");
        return;
    }

    auto* tilemap = new Tilemap(path);
    m_tilemaps.emplace(name, tilemap);
}
Spark::Tilemap* Spark::AssetManager::GetTilemap(const std::string& name){
    auto it = m_tilemaps.find(name);
    if(it == m_tilemaps.end())
        return nullptr;

    return it->second;
}