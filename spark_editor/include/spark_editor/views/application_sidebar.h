#ifndef SPARK_ENGINE_APPLICATION_SIDEBAR_H
#define SPARK_ENGINE_APPLICATION_SIDEBAR_H
#include "spark_editor/base.h"
#include "spark_editor/core/view.h"

class ApplicationSidebar: public View{
public:
    ApplicationSidebar();
    void Render() override;
};
#endif //SPARK_ENGINE_APPLICATION_SIDEBAR_H
