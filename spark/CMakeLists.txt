include_directories(include)
include_directories(${glm_SOURCE_DIR}/include)

cmrc_add_resource_library(spark-resources
        ALIAS spark::rc
        NAMESPACE spark
        resources/WallTile.png
        resources/Overworld.png
        resources/overworld.tm
)

add_library(spark STATIC
        include/spark/spark.h
        include/spark/assets/sprite.h
        include/spark/assets/tilemap.h
        include/spark/core/asset.h
        include/spark/core/application.h
        include/spark/core/asset_manager.h
        include/spark/core/base.h
        include/spark/core/platform.h
        include/spark/core/ecs.h
        include/spark/core/components.h
        include/spark/core/window.h
        include/spark/renderer/opengl.h
        include/spark/renderer/shader.h
        include/spark/renderer/renderer.h
        include/spark/renderer/mesh.h
        include/spark/renderer/texture_2d.h
        include/spark/renderer/vertex_array_object.h
        include/spark/systems/camera_system_2d.h
        include/spark/systems/physics_system_2d.h
        include/spark/systems/sprite_renderer_system.h
        include/spark/systems/tilemap_renderer_system.h
        include/spark/utility/logger.h
        include/spark/utility/time.h

        src/core/application.cpp
        src/core/ecs.cpp
        src/core/window.cpp
        src/renderer/renderer.cpp
        src/systems/physics_system_2d.cpp
        src/systems/sprite_renderer_system.cpp
        src/utility/logger.cpp
        src/utility/time.cpp
        src/renderer/shader.cpp
        src/renderer/mesh.cpp
        src/renderer/texture_2d.cpp
        src/core/asset.cpp
        src/systems/camera_system_2d.cpp
        src/renderer/opengl.cpp
        src/assets/sprite.cpp
        src/core/asset_manager.cpp
        src/assets/tilemap.cpp
        src/systems/tilemap_renderer_system.cpp
        src/renderer/vertex_array_object.cpp
)

target_link_libraries(spark spdlog glfw glad spark::rc)

target_include_directories(spark PUBLIC ${CMAKE_BINARY_DIR}/_cmrc/include)