#ifndef SPARK_ENGINE_VIEW_H
#define SPARK_ENGINE_VIEW_H
#include "spark_editor/base.h"
#include "spark_editor/models/project.h"

struct ViewCallbacks{
    std::function<void()> OnProjectSelected;
};

class View{
public:
    static Project* project;

    static ImGuiIO* io;
    static ViewCallbacks* callbacks;

    View();
    virtual ~View() = 0;
    virtual void Render() = 0;
};

#endif //SPARK_ENGINE_VIEW_H
