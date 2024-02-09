#ifndef SPARK_ENGINE_APPLICATION_H
#define SPARK_ENGINE_APPLICATION_H
#include "spark_editor/base.h"
#include "spark_editor/core/view.h"
#include "spark_editor/views/menu_bar.h"
#include "spark_editor/views/app_window.h"
#include "spark_editor/views/utility_window.h"
#include "spark_editor/views/application_sidebar.h"
#include "spark_editor/views/project_explorer.h"
class Application: public View{
private:
    bool m_firstRender;
    MenuBar m_menuBar;
    AppWindow m_mainWindow;
    UtilityWindow m_utilityWindow;
    ApplicationSidebar m_appSidebar;
    ProjectExplorer m_projectExplorer;
    void SetupDockSpace();
public:
    Application();
    void Render() override;
};

#endif //SPARK_ENGINE_APPLICATION_H
