#ifndef SPARK_ENGINE_APP_WINDOW_H
#define SPARK_ENGINE_APP_WINDOW_H
#include "spark_editor/base.h"
#include "spark_editor/core/view.h"
#include "spark_editor/views/sprite_editor.h"
class AppWindow: public View{
private:
    SpriteEditor m_spriteEditor;
public:
    void Render() override;
};

#endif //SPARK_ENGINE_APP_WINDOW_H
