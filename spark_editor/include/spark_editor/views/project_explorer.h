#ifndef SPARK_ENGINE_PROJECT_EXPLORER_H
#define SPARK_ENGINE_PROJECT_EXPLORER_H
#include "spark_editor/base.h"
#include "spark_editor/core/view.h"

class ProjectExplorer: public View{
    void RenderFolderEntry(const fs::directory_entry& entry);
public:
    void Render() override;
};

#endif //SPARK_ENGINE_PROJECT_EXPLORER_H
