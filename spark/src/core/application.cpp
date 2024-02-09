#include "spark/core/application.h"
#include "spark/core/asset_manager.h"
#include "spark/utility/time.h"
#include "spark/renderer/opengl.h"

Spark::Application::Application(){
    m_window = nullptr;
    m_scene = new Scene();
    m_renderer = nullptr;
}

Spark::Application::~Application() = default;

void Spark::Application::SetWindowTitle(const std::string& title){
    m_window->SetTitle(title);
}

void Spark::Application::SetWindowSize(int width, int height){
    m_window->SetSize(width, height);
}
void Spark::Application::SetRendererScale(float scale){
    m_renderer->SetScale(scale);
}
bool Spark::Application::OnInit() {
    return true;
}

void Spark::Application::OnStart() {
}

void Spark::Application::BuildScene(Spark::Scene* scene){

}

int Spark::Application::Main() {
    Logger::Initialize();

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    m_window = new Window();
    if(!OnInit()){
        delete m_window;
        return 1;
    }

    if(!m_window->Create()){
        Logger::Error("Could not create window");
        delete m_window;
        glfwTerminate();
        return 1;
    }
    m_renderer = new Renderer();
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    OnStart();

    m_scene = new Scene();
    BuildScene(m_scene);
    Time::Initialize();

    while (!m_window->ShouldClose()){
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT);
        Time::NextFrame();
        m_scene->StartFrame();
        m_scene->Update();
        m_scene->Render(m_renderer);
        m_window->SwapBuffer();
    }

    delete m_scene;
    AssetManager::Destroy();
    delete m_renderer;
    delete m_window;
    glfwTerminate();
    return 0;
}