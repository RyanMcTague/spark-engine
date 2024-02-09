#include "spark/systems/camera_system_2d.h"
#include "spark/core/components.h"

void Spark::CameraSystem2D::Setup() {
    RequireComponent<Transform2D>();
    RequireComponent<Camera2D>();
}

void Spark::CameraSystem2D::Render(Spark::Renderer *renderer) {
    auto* window = glfwGetCurrentContext();
    int width, height;
    glfwGetWindowSize(window, &width, &height);

    for(auto entity: entities){
        auto transform = entity->GetComponent<Transform2D>();
        renderer->SetPosition(vec2(-transform->position.x, transform->position.y));
        break;
    }
}