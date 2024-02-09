#ifndef SPARK_ENGINE_BASE_H
#define SPARK_ENGINE_BASE_H
#define IMGUI_USER_CONFIG "spark_editor/imconfig.h"
#include <vector>
#include <map>
#include <fstream>
#include <functional>
#include <filesystem>
#include <cmath>
#include "spdlog/spdlog.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_internal.h"
#include "IconsFontAwesome6.h"
#include "nfd.h"
#include "cmrc/cmrc.hpp"
#include "uuid.h"

CMRC_DECLARE(spark_editor);

namespace fs = std::filesystem;

struct Point{
    int x;
    int y;
};

using UUID = uuids::uuid;

class UUIDGenerator{
private:
    static uuids::uuid_random_generator* m_gen;
public:
    UUIDGenerator() = delete;

    static UUID Create();
    static void Destroy();
};
struct ImVec3 { float x, y, z; explicit ImVec3(float _x = 0.0f, float _y = 0.0f, float _z = 0.0f) { x = _x; y = _y; z = _z; } };
namespace ImGuiTheme{
    void Dracula();
}
#endif //SPARK_ENGINE_BASE_H
