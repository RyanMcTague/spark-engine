#include "spark_editor/views/project_selector.h"
#include "spark_editor/utility/file_dialog.h"


void ProjectSelector::Render() {
    ImGui::SetNextWindowSize(io->DisplaySize);
    ImGui::SetNextWindowPos(ImVec2());
    ImGui::Begin("##project-selector", nullptr, ImGuiWindowFlags_None
                                                | ImGuiWindowFlags_NoMove
                                                | ImGuiWindowFlags_NoResize
                                                | ImGuiWindowFlags_NoTitleBar);
    if (ImGui::Button("New Project"))
    {
        auto result = FileDialog::CreateProject();
        if (result.status == FileDialog::Status::Okay){
            Project::Create(result.path);
            callbacks->OnProjectSelected();
        }
    }

    if (ImGui::Button("Open Project"))
    {
        auto result = FileDialog::OpenProject();
        if (result.status == FileDialog::Status::Okay){
            Project::Open(result.path);
            callbacks->OnProjectSelected();
        }
    }
    ImGui::End();
}