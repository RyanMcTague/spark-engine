#include "spark_editor/core/components.h"


void Component::TileImage(Sprite* tileSheet, uint32_t x, uint32_t y, float scale, const OnTileClicked& onClick){
    auto& tile = tileSheet->tiles[y * tileSheet->tileCount.x + x];

    ImGui::Image((void*)(intptr_t)tileSheet->texture, {
            (float )tileSheet->tileSize.x * scale,
            (float )tileSheet->tileSize.y * scale,
        }, tile.uv0, tile.uv1);

    if (onClick && (ImGui::IsItemClicked(ImGuiMouseButton_Left) ||
                    (ImGui::IsItemHovered() && ImGui::IsMouseDown(ImGuiMouseButton_Left)))){
        onClick(tile);
    }
}

void Component::TileSheetImage(Sprite* tileSheet, float scale, const OnTileClicked& onClick){
    ImVec2 start = ImGui::GetCursorPos();
    for (int y = 0; y < tileSheet->tileCount.y; y++) {
        for (int x = 0; x < tileSheet->tileCount.x; x++) {
            ImGui::SetCursorPos({
                (float )x * (float)tileSheet->tileSize.x * scale + start.x,
                (float )y * (float)tileSheet->tileSize.y * scale + start.y});
            auto& tile = tileSheet->tiles[y * tileSheet->tileCount.x + x];
            Component::TileImage(tileSheet, x, y, scale);
            if (onClick && (ImGui::IsItemClicked(ImGuiMouseButton_Left))){
                onClick(tile);
            }
        }
    }
    ImGui::SetCursorPos({start.x,
                         (float )tileSheet->tileCount.y * (float)tileSheet->tileSize.y * scale + start.y});
}

bool Component::AppButton(const std::string& text, bool active, const ImVec2& size){
    bool skipActive = false;
    bool isClicked = false;
    if (active)
        ImGui::PushStyleColor(ImGuiCol_Button, ImColor(0x16, 0xa3, 0x4a).Value);
    if (ImGui::Button(text.c_str(), size)) {
        isClicked = true;
        skipActive = true;
    }

    if (!skipActive && active)
        ImGui::PopStyleColor();

    return isClicked;
}

