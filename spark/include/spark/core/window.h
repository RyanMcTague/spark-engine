#ifndef SPARK_ENGINE_OPENGL_WINDOW_H
#define SPARK_ENGINE_OPENGL_WINDOW_H
#include "spark/core/base.h"
#include "spark/renderer/opengl.h"

namespace Spark{
    SPARK_API class Window{
    private:
        GLFWwindow* m_handle;
        int m_height;
        int m_width;
        std::string m_title;
    public:
        Window();
         ~Window();
         void SetTitle(const std::string& title);
         void SetSize(int width, int height);
         bool Create();
         [[nodiscard]] bool ShouldClose() const;
         void SwapBuffer() const;
    };
}

#endif //SPARK_ENGINE_OPENGL_WINDOW_H
