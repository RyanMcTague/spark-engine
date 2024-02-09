#include "spark_editor/views/project_explorer.h"

void ProjectExplorer::RenderFolderEntry(const fs::directory_entry& entry){
    auto name = entry.path().string().substr((project->GetBasePath() + "/assets/").size());
    if (ImGui::TreeNode((void*)name.c_str(), "%s", name.c_str()))
    {
        for(const auto& _entry: fs::directory_iterator(entry.path())){
            ImGui::Bullet();
            ImGui::SameLine();
            ImGui::Text("%s", _entry.path().filename().c_str());
        }
        ImGui::TreePop();
    }

}

void ProjectExplorer::Render(){
    ImGui::Begin("ProjectExplorer", nullptr, ImGuiWindowFlags_NoTitleBar);
    for(const auto& entry: fs::directory_iterator(project->GetBasePath() + "/assets")){

        if (entry.is_directory()){
            RenderFolderEntry(entry);
        }else{
            ImGui::Bullet();
            ImGui::SameLine();
            ImGui::Text("%s", entry.path().filename().c_str());
        }
    }
    ImGui::End();
}