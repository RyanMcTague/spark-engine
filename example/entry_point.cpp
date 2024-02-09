#include "spark/spark.h"
using namespace Spark;

int scale = 3;

class EntryPoint: public Application{
public:
    bool OnInit() override;
    void OnStart() override;
    void BuildScene(Scene* scene) override;
};

bool EntryPoint::OnInit() {
    SetWindowTitle("Breakout");
    SetWindowSize(16 * 16 * scale , 16 * 16 * scale);
    return true;
}

void EntryPoint::OnStart() {
    SetRendererScale((float )scale);
    AssetManager::RegisterSprite("wall-sprite", "resources/WallTile.png");
    AssetManager::RegisterSprite("over-world", "resources/Overworld.png", vec2(16, 16));
    AssetManager::RegisterTilemap("my-map", "resources/overworld.tm");
}

void EntryPoint::BuildScene(Scene* scene){
    auto camera = scene->CreateEntity("SceneCamera");
    camera->AddComponent<Transform2D>(vec2(0, 0));
    camera->AddComponent<Camera2D>();
    camera->AddComponent<RigidBody2D>(vec2(0.0f, 0.0f));
    camera->Tag("controllable");

    auto tilemap = scene->CreateEntity();
    tilemap->AddComponent<Transform2D>(vec2(0, 0));
    tilemap->AddComponent<TilemapRenderer>("my-map" ,"over-world");

    auto player = scene->CreateEntity("Player");
    player->AddComponent<Transform2D>(vec2(0, 0));
    player->AddComponent<SpriteRenderer>("wall-sprite");
    player->AddComponent<RigidBody2D>(vec2(10.0f, 0.0f));
};

SPARK_DECLARE_APP(EntryPoint)
