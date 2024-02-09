#ifndef SPARK_ENGINE_COMPONENTS_H
#define SPARK_ENGINE_COMPONENTS_H
#include "spark/core/base.h"
#include "spark/renderer/mesh.h"
namespace Spark{

    SPARK_API struct Transform2D{
        vec2 position{};
        float rotation;
        vec2 scale{};

        explicit Transform2D(const vec2& position = vec2(0), float rotation = 0.0f, const vec2& scale = vec2(1.0f)){
            this->position = position;
            this->rotation = rotation;
            this->scale = scale;
        }
    };

    SPARK_API struct RigidBody2D
    {
        vec2 velocity = vec2();

        RigidBody2D(const RigidBody2D& rb){
            velocity = rb.velocity;
        }

        explicit RigidBody2D(const vec2& velocity = vec2()){
            this->velocity = velocity;
        }
    };

    SPARK_API struct Camera2D{
    };

    struct SpriteRenderer{
        std::string sprite;
        vec2 tile{};
        explicit SpriteRenderer(const std::string& sprite, const vec2& tile = vec2(0)){
            this->sprite = sprite;
            this->tile = tile;
        }
    };

    SPARK_API struct TilemapRenderer{
        std::string sprite;
        std::string tilemap;
        explicit TilemapRenderer(const std::string& tilemap, const std::string& sprite){
            this->tilemap = tilemap;
            this->sprite = sprite;
        }
    };
}

#endif //SPARK_ENGINE_COMPONENTS_H
