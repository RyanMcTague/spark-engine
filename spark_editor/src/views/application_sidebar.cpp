#include "spark_editor/views/application_sidebar.h"
#include "spark_editor/core/components.h"

ApplicationSidebar::ApplicationSidebar() = default;

void ApplicationSidebar::Render(){
    ImGui::Begin("Sidebar", nullptr, ImGuiWindowFlags_NoTitleBar);
    ImGui::End();
}
