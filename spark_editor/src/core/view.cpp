#include "spark_editor/core/view.h"

ViewCallbacks* View::callbacks = nullptr;
ImGuiIO* View::io = nullptr;
Project* View::project = nullptr;

View::View() = default;
View::~View() = default;
