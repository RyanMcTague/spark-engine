#include "spark/systems/sprite_renderer_system.h"
#include "spark/core/components.h"
#include "spark/core/asset_manager.h"
void Spark::SpriteRendererSystem::Setup() {
    RequireComponent<Transform2D>();
    RequireComponent<SpriteRenderer>();
}

void Spark::SpriteRendererSystem::Render(Renderer* renderer) {
    for(auto entity: entities){
        auto sp = entity->GetComponent<SpriteRenderer>();
        auto transform = entity->GetComponent<Transform2D>();
        auto* sprite = AssetManager::GetSprite(sp->sprite);
        renderer->DrawSprite(
                transform->position,
                transform->scale,
                sprite->GetTileSize(),
                sp->tile,
                transform->rotation,
                sprite->GetTexture());
    }
}


