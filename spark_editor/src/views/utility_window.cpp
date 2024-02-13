#include "spark_editor/views/utility_window.h"

void UtilityWindow::Render(){
    ImGui::Begin("Utility", nullptr, ImGuiWindowFlags_NoTitleBar);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, {0,0});
    ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4{0.05f, 0.05f, 0.065f, 1.0f});
    ImGui::BeginChild("##util-project-explorer", { 150.0f, ImGui::GetWindowHeight() });
    ImGui::PopStyleVar();
    ImGui::PopStyleColor();

    if(ImGui::TreeNode("Scripts")){
        ImGui::TreePop();
    }
    if(ImGui::TreeNode("Tilesheets")){
        ImGui::TreePop();
    }
    if(ImGui::TreeNode("Tilemaps")){
        ImGui::TreePop();
    }
    if(ImGui::TreeNode("Sprites")){
        ImGui::TreePop();
    }
    ImGui::EndChild();
    ImGui::End();
}