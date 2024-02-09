#ifndef SPARK_ENGINE_TILEMAP_H
#define SPARK_ENGINE_TILEMAP_H
#include "spark/core/base.h"

namespace Spark{
    SPARK_API class Tilemap{
    private:
        void Parse(const std::string& source);
    public:
        std::vector<std::vector<vec2>> layers;
        int tilesX;
        int tilesY;
        explicit Tilemap(const std::string& path);
        ~Tilemap();
    };
}

#endif //SPARK_ENGINE_TILEMAP_H
