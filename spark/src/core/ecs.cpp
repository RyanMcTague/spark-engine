#include "spark/core/ecs.h"
#include "spark/core/components.h"
#include "spark/systems/physics_system_2d.h"
#include "spark/systems/sprite_renderer_system.h"
#include "spark/systems/camera_system_2d.h"
#include "spark/systems/tilemap_renderer_system.h"
/************************************************
 * Spark::Signature
 ***********************************************/

Spark::Signature::Signature() = default;

void Spark::Signature::Set(uint32_t n){
    m_signature.set(n);
}

bool Spark::Signature::Test(uint32_t n){
    return m_signature.test(n);
}

void Spark::Signature::Clear(uint32_t n){
    m_signature.reset(n);
}

bool Spark::Signature::Compare(const Signature& other) const{
    bool success = true;

    for (uint32_t i = 0; i < MAX_COMPONENTS; i++) {
        if (m_signature.test(i) && !other.m_signature.test(i)){
            success = false;
            break;
        }
    }
    return success;
}

/************************************************
 * Spark::Entity
 ***********************************************/
const Spark::EntityList NullEntityList;

Spark::UUID Spark::Entity::m_nextID = 0;

std::stack<Spark::UUID> Spark::Entity::m_freeIDs;

Spark::Entity::Entity(Scene* scene,  const std::string& name) {
    m_scene = scene;
    m_id = PopID();
    m_name = name;
}

void Spark::Entity::PushID(Spark::UUID id) {
    m_freeIDs.push(id);
}

Spark::UUID Spark::Entity::PopID() {
    if (m_freeIDs.empty())
        return m_nextID++;

    UUID id = m_freeIDs.top();
    m_freeIDs.pop();
    return id;
}

void Spark::Entity::ResetIDs()  {
    m_nextID = 0;
    m_freeIDs = std::stack<Spark::UUID>();
}

Spark::UUID Spark::Entity::GetID() const {
    return m_id;
}

const std::string& Spark::Entity::GetName(){
    return m_name;
}

void Spark::Entity::Destroy(){
    m_scene->DestroyEntity(this);
}
void Spark::Entity::Tag(const std::string& tag){
    m_scene->TagEntity(this, tag);
}

/************************************************
 * Spark::IComponent
 ***********************************************/

Spark::TypeMap<Spark::UUID> Spark::IComponent::m_ids;

Spark::UUID Spark::IComponent::m_nextID = 0;

void Spark::IComponent::ResetIDs()  {
    m_nextID = 0;
}

Spark::IComponentPool::~IComponentPool() = default;

/************************************************
 * Spark::System
 ***********************************************/

Spark::System::~System() = default;

bool Spark::System::BelongsToSystem(Entity* entity) const{
    return m_signature.Compare(entity->signature);
}

void Spark::System::AddToSystem(Entity* entity){
    entities.push_back(entity);
}

void Spark::System::RemoveFromSystem(Entity* entity){
    auto it = std::find(entities.begin(), entities.end(), entity);
    if (it != entities.end())
        entities.erase(it);
}

void Spark::System::SetScene(Scene* s){
    this->scene = s;
}
/************************************************
* Spark::TagPool
***********************************************/

void Spark::TagPool::AddEntity(Spark::Entity* entity){
    auto it = std::find(m_pool.begin(), m_pool.end(), entity);
    if (it == m_pool.end()){
        m_pool.push_back(entity);
    }
}
void Spark::TagPool::RemoveEntity(Spark::Entity* entity){
    auto it = std::find(m_pool.begin(), m_pool.end(), entity);
    if (it != m_pool.end()){
        m_pool.erase(it);
    }
}
bool Spark::TagPool::ContainsEntity(Spark::Entity* entity){
    auto it = std::find(m_pool.begin(), m_pool.end(), entity);
    return it != m_pool.end();
}

const Spark::EntityList& Spark::TagPool::GetEntityList(){
    return m_pool;
}


/************************************************
 * Spark::Scene
 ***********************************************/

Spark::Scene::Scene(){
    RegisterSystem<CameraSystem2D>();
    RegisterSystem<PhysicsSystem2D>();
    RegisterSystem<SpriteRendererSystem>();
    RegisterSystem<TilemapRendererSystem>();
};

Spark::Scene::~Scene() {
    for(auto* entity: m_entities){
        delete entity;
    }

    for(auto& el: m_systems){
        delete el.second;
    }

    for(auto& el: m_pools){
        delete el.second;
    }

    for(auto& el: m_entityTags) {
        delete el.second;
    }

    Entity::ResetIDs();
    IComponent::ResetIDs();
}

void Spark::Scene::StartFrame(){
    for(auto* entity: m_destroyedEntites){
        auto it = std::find_if(m_entityNames.begin(), m_entityNames.end(), [entity](const auto& el)
            { return el.first == entity->GetName(); }
        );

        if(it != m_entityNames.end() && it->second == 0){
            m_entityNames.erase(it);
        }else if(it != m_entityNames.end()){
            m_entityNames[it->first] = it->second - 1;
        }

        UUID id = entity->GetID();
        for (auto& el: m_pools) {
            auto *pool = el.second;
            if(entity->signature.Test(pool->GetComponentID())){
                pool->Remove(entity);
            }
        }

        for(auto& el: m_systems){
            el.second->RemoveFromSystem(entity);
        }

        for(auto& el: m_entityTags){
            el.second->RemoveEntity(entity);
        }

        Entity::PushID(id);
        delete entity;
        Logger::Info("Destroyed Entity<" + std::to_string(id) + ">");

        m_entities[id] = nullptr;
    }

    m_destroyedEntites.clear();
}

Spark::Entity *Spark::Scene::CreateEntity(const std::string& name) {

    std::string entityName;
    if (name.empty()){
        entityName = "entity<" + std::to_string(m_entities.size()) + ">";
    } else{
        auto it = m_entityNames.find(name);
        if (it != m_entityNames.end()){
            entityName = name + "-" + std::to_string(it->second + 1);
            m_entityNames[name] =  m_entityNames[name] + 1;
        }else{
            entityName = name;
            m_entityNames.emplace(name, 0);
        }
    }

    auto* entity = new Entity(this, entityName);

    if (entity->GetID() >= m_entities.size()){
        m_entities.push_back(entity);
    } else{
        m_entities[entity->GetID()] = entity;
    }
    return entity;
}

Spark::Entity* Spark::Scene::GetEntityByName(const std::string& name){
    auto it = std::find_if(m_entities.begin(), m_entities.end(), [name](Entity* entity)
        { return entity->GetName() == name; }
    );
    return it != m_entities.end() ? *it : nullptr;
}
const Spark::EntityList& Spark::Scene::GetEntityListByTag(const std::string& tag){
    auto it = m_entityTags.find(tag);
    if(it == m_entityTags.end()){
        return NullEntityList;
    }
    return it->second->GetEntityList();
}

void Spark::Scene::TagEntity(Entity* entity, const std::string& tag){
    auto it = m_entityTags.find(tag);
    TagPool* pool;
    if(it == m_entityTags.end()){
        pool = new TagPool();
        m_entityTags.emplace(tag, pool);
    } else if(it->second->ContainsEntity(entity)){
        return;
    }else{
        pool = it->second;
    }

    pool->AddEntity(entity);
}
void Spark::Scene::DestroyEntity(Spark::Entity *entity) {
    auto it = std::find(m_destroyedEntites.begin(), m_destroyedEntites.end(), entity);
    if (it == m_destroyedEntites.end()){
        Logger::Info("Marking Entity<" + std::to_string(entity->GetID()) + "> as destroyed");
        m_destroyedEntites.push_back(entity);
    }
}

void Spark::Scene::Update() {
    GetSystem<PhysicsSystem2D>()->Update();
}

void Spark::Scene::Render(Renderer* renderer) {
    GetSystem<CameraSystem2D>()->Render(renderer);
    GetSystem<TilemapRendererSystem>()->Render(renderer);
    GetSystem<SpriteRendererSystem>()->Render(renderer);
}
