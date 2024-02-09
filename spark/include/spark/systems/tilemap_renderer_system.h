#ifndef SPARK_ENGINE_TILEMAP_RENDERER_SYSTEM_H
#define SPARK_ENGINE_TILEMAP_RENDERER_SYSTEM_H
#include "spark/core/base.h"
#include "spark/core/ecs.h"

namespace Spark{
    SPARK_API class TilemapRendererSystem: public System{
    public:
        void Setup() override;
        void Render(Renderer* renderer) override;
    };
}

#endif //SPARK_ENGINE_TILEMAP_RENDERER_SYSTEM_H
