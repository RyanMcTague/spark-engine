#include "spark/core/window.h"

Spark::Window::Window() {
    m_width = 0;
    m_height = 0;
    m_title = "";
    m_handle = nullptr;
}

Spark::Window::~Window(){
    if (m_handle){
        glfwDestroyWindow(m_handle);
    }
}

void Spark::Window::SetTitle(const std::string& title){
    m_title = title;
}

void Spark::Window::SetSize(int width, int height){
    m_width = width;
    m_height = height;
}

bool Spark::Window::Create() {
    if (m_handle)
        return false;
    m_handle = glfwCreateWindow(m_width, m_height, m_title.c_str(), nullptr, nullptr);
    glfwMakeContextCurrent(m_handle);
    glfwSetWindowUserPointer(m_handle, (void*)this);
    if (m_handle && !gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        Logger::Error("Failed to initialize GLAD");
        glfwDestroyWindow(m_handle);
        m_handle = nullptr;
    }

    return m_handle != nullptr;
}

bool Spark::Window::ShouldClose() const{
    return glfwWindowShouldClose(m_handle);
}

void Spark::Window::SwapBuffer() const{
    glfwSwapBuffers(m_handle);
}
