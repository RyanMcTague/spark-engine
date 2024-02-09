#include "spark/systems/physics_system_2d.h"
#include "spark/core/components.h"
#include "spark/utility/time.h"
void Spark::PhysicsSystem2D::Setup() {
    RequireComponent<Transform2D>();
    RequireComponent<RigidBody2D>();
}

void Spark::PhysicsSystem2D::Update() {
    float deltaTime = Time::DeltaTime();
    for(auto entity: entities){
        auto rb = entity->GetComponent<RigidBody2D>();
        auto transform = entity->GetComponent<Transform2D>();
        transform->position.x += rb->velocity.x * deltaTime;
        transform->position.y += rb->velocity.y * deltaTime;
    }
}
