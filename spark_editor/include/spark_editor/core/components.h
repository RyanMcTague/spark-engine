#ifndef SPARK_ENGINE_COMPONENTS_H
#define SPARK_ENGINE_COMPONENTS_H
#include "spark_editor/base.h"
#include "spark_editor/models/project.h"

namespace Component{
        void TileImage(Sprite* tileSheet, uint32_t x, uint32_t y,
                       float scale = 1.0f, const OnTileClicked& onClick = OnTileClicked());
        void TileSheetImage(Sprite* tileSheet, float scale = 1.0f, const OnTileClicked& onClick = OnTileClicked());

        bool AppButton(const std::string& text, bool active, const ImVec2& size = ImVec2(0, 0));
}
#endif //SPARK_ENGINE_COMPONENTS_H
