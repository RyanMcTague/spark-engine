#include "spark_editor/views/menu_bar.h"
#include "spark_editor/utility/file_dialog.h"


void MenuBar::Render(){
    ImGui::BeginMenuBar();
    if (ImGui::BeginMenu("File")){
        if (ImGui::MenuItem("Open"))
            spdlog::debug("open");
        if (ImGui::MenuItem("Save"))
            spdlog::debug("Save");

        ImGui::Separator();

        if (ImGui::MenuItem("Import Sprite"))
            spdlog::debug("sprite");
        ImGui::EndMenu();
    }

    if (ImGui::BeginMenu("Project")){
        if (ImGui::BeginMenu("Create")){
            if (ImGui::MenuItem("Sprite")){}
            if (ImGui::MenuItem("Tile Sheet")){}
            if (ImGui::MenuItem("Tile Map")){}
            ImGui::EndMenu();
        }
        ImGui::EndMenu();
    }


    ImGui::EndMenuBar();
}
