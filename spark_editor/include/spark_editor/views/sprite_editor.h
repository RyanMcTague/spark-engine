#ifndef SPARK_ENGINE_SPRITE_EDITOR_H
#define SPARK_ENGINE_SPRITE_EDITOR_H
#include "spark_editor/base.h"
#include "spark_editor/core/view.h"
#include "spark_editor/utility/texture.h"
class SpriteEditor: public View{
private:
    ImVec2 windowSize;
    ImVec2 editorSize;
    ImVec2 toolbarSize;
    ImVec2 size;
    ImVec2 canvasSize;
    uint32_t data[64 * 64]{};
    Texture sprite;
public:
    SpriteEditor();
    ~SpriteEditor() override;
    void Render() override;
};

#endif //SPARK_ENGINE_SPRITE_EDITOR_H
