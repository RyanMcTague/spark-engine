#ifndef SPARK_ENGINE_SPARK_H
#define SPARK_ENGINE_SPARK_H

#include "spark/core/base.h"

#include "spark/assets/sprite.h"
#include "spark/assets/tilemap.h"

#include "spark/core/application.h"
#include "spark/core/asset_manager.h"
#include "spark/core/asset.h"
#include "spark/core/components.h"
#include "spark/core/ecs.h"
#include "spark/core/platform.h"
#include "spark/core/window.h"

#include "spark/renderer/renderer.h"
#include "spark/renderer/opengl.h"
#include "spark/renderer/shader.h"
#include "spark/renderer/texture_2d.h"
#include "spark/renderer/mesh.h"
#include "spark/renderer/vertex_array_object.h"

#include "spark/systems/camera_system_2d.h"
#include "spark/systems/physics_system_2d.h"
#include "spark/systems/sprite_renderer_system.h"
#include "spark/systems/tilemap_renderer_system.h"

#include "spark/utility/logger.h"
#include "spark/utility/time.h"

#define SPARK_DECLARE_APP(IApp) \
int main(int argc, char **argv){\
    auto* app = new IApp();     \
    int ret = app->Main();      \
    delete app;                 \
    return ret;                 \
}

#endif //SPARK_ENGINE_SPARK_H

