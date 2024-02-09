#ifndef SPARK_ENGINE_APPLICATION_H
#define SPARK_ENGINE_APPLICATION_H
#include "spark/core/base.h"
#include "spark/core/window.h"
#include "spark/core/ecs.h"
#include "spark/renderer/renderer.h"
namespace Spark{

    SPARK_API class Application{
    private:
        Window* m_window;
        Scene* m_scene;
        Renderer* m_renderer;
    protected:
        void SetWindowTitle(const std::string& title);
        void SetWindowSize(int width, int height);
        void SetRendererScale(float scale);
        virtual bool OnInit();
        virtual void OnStart();
        virtual void BuildScene(Scene* scene);

    public:
        Application();
        virtual ~Application() = 0;
        int Main();
    };
}

#endif //SPARK_ENGINE_APPLICATION_H
