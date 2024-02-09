#ifndef SPARK_ENGINE_PHYSICS_SYSTEM_2D_H
#define SPARK_ENGINE_PHYSICS_SYSTEM_2D_H
#include "spark/core/base.h"
#include "spark/core/ecs.h"

namespace Spark{
    SPARK_API class PhysicsSystem2D: public System{
    public:
        void Setup() override;
        void Update() override;
    };
}

#endif //SPARK_ENGINE_PHYSICS_SYSTEM_2D_H