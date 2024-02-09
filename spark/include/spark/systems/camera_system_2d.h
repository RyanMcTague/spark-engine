#ifndef SPARK_ENGINE_CAMERA_SYSTEM_2D_H
#define SPARK_ENGINE_CAMERA_SYSTEM_2D_H
#include "spark/core/base.h"
#include "spark/core/ecs.h"

namespace Spark{
    SPARK_API class CameraSystem2D: public System{
    public:
        void Setup() override;
        void Render(Renderer* renderer) override;
    };
}

#endif //SPARK_ENGINE_CAMERA_SYSTEM_2D_H
