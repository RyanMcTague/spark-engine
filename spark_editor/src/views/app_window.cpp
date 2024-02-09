#include "spark_editor/views/app_window.h"
void AppWindow::Render(){
    ImGui::Begin("AppWindow", nullptr, ImGuiWindowFlags_NoTitleBar);
    m_spriteEditor.Render();
    ImGui::End();
}
