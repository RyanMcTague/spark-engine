#include "spark_editor/views/sprite_editor.h"

SpriteEditor::SpriteEditor() {

}

SpriteEditor::~SpriteEditor() = default;

void SpriteEditor::Render(){
    windowSize = ImGui::GetWindowSize();
    size = windowSize;
    auto padding = ImGui::GetStyle().WindowPadding;
    size.x -= 3 * padding.x;
    size.y -= 5 * padding.y;
    toolbarSize = { size.x * 0.10f, size.y};
    editorSize = { size.x * 0.90f, size.y};

    ImGui::BeginChild("##sprite-editor-tools", toolbarSize);
    ImGui::Button(ICON_FA_PAINT_ROLLER);
    static ImVec4 color(0.23f, 1.0f, 1.0f, 1.0f);
    static ImGuiColorEditFlags colorEditFlags = 0
            | ImGuiColorEditFlags_NoInputs
            | ImGuiColorEditFlags_NoLabel
            | ImGuiColorEditFlags_NoDragDrop
            | ImGuiColorEditFlags_AlphaPreview
            | ImGuiColorEditFlags_NoOptions;

    ImGui::Spacing();
    ImGui::ColorEdit4("MyColor##3", (float*)&color, colorEditFlags);
    ImGui::EndChild();

    ImGui::SameLine();

    ImGui::BeginChild("##sprite-editor-main", editorSize);

    ImGui::EndChild();
}
