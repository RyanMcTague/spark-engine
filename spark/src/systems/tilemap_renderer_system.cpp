#include "spark/systems/tilemap_renderer_system.h"
#include "spark/core/components.h"
#include "spark/core/asset_manager.h"

void Spark::TilemapRendererSystem::Setup() {
    RequireComponent<Transform2D>();
    RequireComponent<TilemapRenderer>();
}

void Spark::TilemapRendererSystem::Render(Renderer* renderer) {
    for(auto entity: entities){
        auto transform = entity->GetComponent<Transform2D>();
        auto tr = entity->GetComponent<TilemapRenderer>();
        auto* sprite = AssetManager::GetSprite(tr->sprite);
        auto* tilemap = AssetManager::GetTilemap(tr->tilemap);
        const vec2& tileSize = sprite->GetTileSize();
        for (int layer = 0; layer < tilemap->layers.size(); layer++) {
            for (int y = 0; y < tilemap->tilesY; y++) {
                for (int x = 0; x < tilemap->tilesX; x++) {
                    vec2 position = transform->position;
                    position.x += tileSize.x * transform->scale.x * (float)x;
                    position.y += tileSize.y * transform->scale.y * (float)y;
                    renderer->DrawSprite(
                            position,
                            transform->scale,
                            sprite->GetTileSize(),
                            tilemap->layers[layer][y * tilemap->tilesX + x],
                            transform->rotation,
                            sprite->GetTexture());
                }
            }
        }
    }
}