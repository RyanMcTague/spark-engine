#ifndef SPARK_ENGINE_TIME_H
#define SPARK_ENGINE_TIME_H
#include "spark/core/base.h"

namespace Spark{
    SPARK_API struct Time{
    private:
        static float m_deltaTime;
        static bool m_shouldUpdate;
        static double m_lastTime;
    public:
        static void Initialize();
        static float DeltaTime();

        static void NextFrame();
        static bool ShouldUpdateFrame();
    };
}
#endif //SPARK_ENGINE_TIME_H
