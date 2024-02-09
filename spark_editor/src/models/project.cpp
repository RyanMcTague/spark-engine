#include "spark_editor/models/project.h"
#include "spark_editor/utility/texture.h"
#include "spark_editor/utility/file_system.h"
Project* Project::m_instance = nullptr;

static std::vector<std::string> s_directories = {
        "assets",
        "assets/sprites",
        "assets/tilesheets",
        "assets/tilemaps",
};

Project::Project(const std::string& path, bool isNew){
    m_basePath =  FileSystem::GetBaseDirFromPath(path);
    m_name = FileSystem::GetFileNameFromPath(path);
    if (isNew){
        std::ofstream outFile(m_basePath + "/" + m_name);
        outFile.close();

    }

    for(const auto& p: s_directories){
        if(!fs::exists(m_basePath + "/" + p)){
            fs::create_directory(m_basePath + "/" + p);
        }
    }
}

Project::~Project(){
    for(const auto& el: m_sprites)
        delete el.second;
    for(const auto& el: m_tileMaps)
        delete el.second;
}

Project* Project::Get(){
    return m_instance;
}
void Project::Destroy(){
    delete m_instance;
}

Project* Project::Create(const std::string& path){
    Destroy();
    m_instance = new Project(path, true);
    return m_instance;
}

Project* Project::Open(const std::string& path){
    Destroy();
    m_instance = new Project(path, false);
    return m_instance;
}
const std::string& Project::GetBasePath(){
    return m_basePath;
}

const std::string& Project::GetName(){
    return m_name;
}

Sprite* Project::GetSprite(const std::string& path){
    auto it = m_sprites.find(path);
    return it == m_sprites.end() ? nullptr : it->second;
}

Sprite* Project::AddSprite(const std::string& path){
    auto it = m_sprites.find(path);

    if (it != m_sprites.end())
        return it->second;

    auto* sprite = new Sprite(path);
    m_sprites.emplace(path, sprite);
    return sprite;
}

TileMap* Project::AddTileMap(const std::string& path){
    auto it = m_tileMaps.find(path);

    if (it != m_tileMaps.end())
        return it->second;

    auto* tileMap = new TileMap(path);
    m_tileMaps.emplace(path, tileMap);
    return tileMap;
}

TileMap* Project::GetTileMap(const std::string& path){
    auto it = m_tileMaps.find(path);
    return it == m_tileMaps.end() ? nullptr : it->second;
}