#include "spark_editor/views/application.h"
ImGuiWindowFlags windowFlags = ImGuiWindowFlags_None
                               | ImGuiWindowFlags_NoMove
                               | ImGuiWindowFlags_NoResize
                               | ImGuiWindowFlags_NoTitleBar
                               | ImGuiWindowFlags_MenuBar;

ImGuiDockNodeFlags dockSpaceFlags = ImGuiDockNodeFlags_PassthruCentralNode;

Application::Application() {
    m_firstRender = true;
}

void Application::SetupDockSpace() {
    ImGuiID dockSpaceId = ImGui::GetID("MyDockSpace");
    ImGui::DockSpace(dockSpaceId, ImVec2());
    ImVec2 size = io->DisplaySize;
    auto consoleWindowSize = ImVec2(size.x, size.y * 0.25f);
    auto mainWindowSize = ImVec2(size.x * 0.85f, size.y * 0.75f);
    auto sidebarSize = ImVec2(size.x * 0.15f, size.y);
    if (m_firstRender){
        m_firstRender = false;
        ImGui::DockBuilderRemoveNode(dockSpaceId);
        ImGui::DockBuilderAddNode(dockSpaceId, dockSpaceFlags | ImGuiDockNodeFlags_DockSpace);

        ImGui::DockBuilderSetNodeSize(dockSpaceId, ImGui::GetWindowSize());

        auto dockIdExplorer = ImGui::DockBuilderSplitNode(dockSpaceId, ImGuiDir_Left, 1, nullptr, &dockSpaceId);
        auto dockIdEditor = ImGui::DockBuilderSplitNode(dockSpaceId, ImGuiDir_Right, 1, nullptr, &dockSpaceId);
        auto dockIdConsole = ImGui::DockBuilderSplitNode(dockSpaceId, ImGuiDir_Down, 1, nullptr, &dockIdEditor);

        ImGui::DockBuilderSetNodeSize(dockIdConsole, consoleWindowSize);
        ImGui::DockBuilderSetNodeSize(dockIdExplorer, sidebarSize);
        ImGui::DockBuilderSetNodeSize(dockIdEditor, mainWindowSize);

        ImGui::DockBuilderDockWindow("AppWindow", dockIdEditor);
        ImGui::DockBuilderDockWindow("Sidebar", dockIdExplorer);
        ImGui::DockBuilderDockWindow("ProjectExplorer", dockIdExplorer);
        ImGui::DockBuilderDockWindow("Utility", dockIdConsole);

        ImGui::DockBuilderFinish(dockSpaceId);
    }

}
void Application::Render() {
    ImGui::SetNextWindowSize(io->DisplaySize);
    ImGui::SetNextWindowPos(ImVec2());
    ImGui::Begin("##main-window", nullptr, windowFlags);
    m_menuBar.Render();
    SetupDockSpace();
    m_mainWindow.Render();
    m_utilityWindow.Render();
    m_appSidebar.Render();
    m_projectExplorer.Render();
    ImGui::End();
}
