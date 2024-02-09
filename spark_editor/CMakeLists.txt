
include_directories(include)

cmrc_add_resource_library(sparkeditor-resources
        ALIAS sparkeditor::rc
        NAMESPACE spark_editor
        resources/fonts/DroidSans.ttf
        resources/fonts/fa-regular-400.ttf
        resources/fonts/fa-solid-900.ttf
)

if (DEFINED SPARK_DATABASE)
    add_compile_definitions(SPARK_DATABASE="${PROJECT_SOURCE_DIR}/${SPARK_DATABASE}")
endif ()
add_executable(spark_editor
        ${CMAKE_SOURCE_DIR}/vendor/imgui/src/imgui.cpp
        ${CMAKE_SOURCE_DIR}/vendor/imgui/src/imgui_demo.cpp
        ${CMAKE_SOURCE_DIR}/vendor/imgui/src/imgui_draw.cpp
        ${CMAKE_SOURCE_DIR}/vendor/imgui/src/imgui_impl_glfw.cpp
        ${CMAKE_SOURCE_DIR}/vendor/imgui/src/imgui_impl_opengl3.cpp
        ${CMAKE_SOURCE_DIR}/vendor/imgui/src/imgui_tables.cpp
        ${CMAKE_SOURCE_DIR}/vendor/imgui/src/imgui_widgets.cpp

        src/main.cpp
        src/base.cpp

        include/spark_editor/base.h
        include/spark_editor/imconfig.h
        include/spark_editor/models/project.h
        include/spark_editor/models/sprite.h
        include/spark_editor/models/tile_map.h

        include/spark_editor/utility/file_dialog.h
        include/spark_editor/utility/file_system.h
        include/spark_editor/utility/texture.h

        include/spark_editor/core/components.h
        include/spark_editor/core/database.h
        include/spark_editor/core/view.h

        include/spark_editor/views/application_sidebar.h
        include/spark_editor/views/utility_window.h
        include/spark_editor/views/project_explorer.h
        include/spark_editor/views/app_window.h
        include/spark_editor/views/application.h
        include/spark_editor/views/menu_bar.h

        src/utility/file_dialog.cpp
        src/utility/file_system.cpp
        src/utility/texture.cpp

        src/core/database.cpp
        src/core/components.cpp
        src/core/view.cpp

        src/views/menu_bar.cpp
        src/views/application.cpp
        src/views/app_window.cpp
        src/views/project_explorer.cpp
        src/views/utility_window.cpp
        src/views/application_sidebar.cpp

        src/models/project.cpp
        src/models/sprite.cpp
        src/models/tile_map.cpp
        include/spark_editor/views/project_selector.h
        src/views/project_selector.cpp
        include/spark_editor/views/sprite_editor.h
        src/views/sprite_editor.cpp
        src/utility/theme.cpp
)

target_link_libraries(spark_editor sparkeditor::rc glfw glad nfd
        spdlog SQLiteCpp sqlite3)

target_include_directories(spark_editor
        PRIVATE ${CMAKE_SOURCE_DIR}/vendor/imgui/include
        PRIVATE ${CMAKE_BINARY_DIR}/_cmrc/include
        PRIVATE ${CMAKE_BINARY_DIR}/_deps/sqlitecpp-src/include
        PRIVATE ${CMAKE_BINARY_DIR}/_deps/stduuid-src/include
)