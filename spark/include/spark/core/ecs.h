#ifndef SPARK_ENGINE_ECS_H
#define SPARK_ENGINE_ECS_H
#include "spark/core/base.h"
#include "spark/renderer/renderer.h"
namespace Spark{

    class Scene;
    /************************************************
     * Spark::Signature
     ***********************************************/

    SPARK_API class Signature{
    public:
        static constexpr uint32_t MAX_COMPONENTS = 100;
    private:
        std::bitset<MAX_COMPONENTS> m_signature;

    public:
        Signature();

        void Set(uint32_t n);
        bool Test(uint32_t n);
        void Clear(uint32_t n);

        [[nodiscard]] bool Compare(const Signature& other) const;
    };

    /************************************************
     * Spark::Entity
     ***********************************************/

    SPARK_API class Entity{
    private:
        static UUID m_nextID;
        static std::stack<UUID> m_freeIDs;
        std::string m_name;
        UUID m_id;
        Scene* m_scene;

    public:
        Signature signature;

        static void PushID(UUID id);
        static UUID PopID();
        static void ResetIDs();

        explicit Entity(Scene* scene, const std::string& name = "");

        [[nodiscard]] UUID GetID() const;
        const std::string& GetName();
        void Destroy();
        void Tag(const std::string& tag);

        template<typename T, typename ...TArgs>
        T* AddComponent(TArgs&& ...args);

        template<typename T>
        T* GetComponent();

        template<typename T>
        bool HasComponent();

        template<typename T>
        void RemoveComponent();
    };

    SPARK_API using EntityList = std::vector<Entity*>;
    /************************************************
     * Spark::IComponent
     ***********************************************/
    SPARK_API class IComponent{
    protected:
        static TypeMap<UUID> m_ids;
        static UUID m_nextID;
    public:
        static void ResetIDs();
    };

    /************************************************
     * Spark::Component
     ***********************************************/
    template<typename T>
    SPARK_API class Component: public IComponent{
    public:
        static UUID GetID(){
            auto it = m_ids.find(typeid(T));

            if(it != m_ids.end()){
                return it->second;
            }

            UUID id = m_nextID++;
            m_ids.emplace(typeid(T), id);
            return id;
        }
    };

    /************************************************
     * Spark::IComponentPool
     ***********************************************/
    SPARK_API class IComponentPool {
    public:
        virtual ~IComponentPool() = 0;
        virtual void Remove(Entity* entity) = 0;
        virtual bool HasEntity(Entity *entity) = 0;
        [[nodiscard]] virtual UUID GetComponentID() const = 0;
    };

    /************************************************
     * Spark::ComponentPool
     ***********************************************/
    template<typename T>
    SPARK_API class ComponentPool: public IComponentPool{
    private:
        std::map<Entity*, T*> m_components;
    public:
        ~ComponentPool() override{
            for(auto& el: m_components){
                delete el.second;
            }
        }

        void Register(Entity *entity, T* component){
            auto it = m_components.find(entity);
            if(it != m_components.end()){
                m_components[entity] = component;
            }else{
                m_components.emplace(entity, component);

            }
        }

        T* Get(Entity* entity) {
            auto it = m_components.find(entity);
            if(it == m_components.end()){
                return nullptr;
            }
            return it->second;
        }

        bool HasEntity(Entity *entity) override {
            auto it = m_components.find(entity);
            return it != m_components.end();
        }

        void Remove(Entity* entity) override {
            auto it = m_components.find(entity);
            if(it != m_components.end()){
                delete it->second;
                m_components.erase(it);
            }
        }

        [[nodiscard]] UUID GetComponentID() const override{
            return Component<T>::GetID();
        }
    };

    /************************************************
     * Spark::System
     ***********************************************/
    SPARK_API class System{
    private:
        Signature m_signature;
    protected:
        EntityList entities;
        Scene* scene;
    public:
        virtual ~System() = 0;

        template<typename T>
        void RequireComponent();

        bool BelongsToSystem(Entity* entity) const;
        void AddToSystem(Entity* entity);
        void RemoveFromSystem(Entity* entity);
        void SetScene(Scene* s);

        virtual void Setup() = 0;
        virtual void Update() {}
        virtual void Render(Renderer* renderer) {}
    };

    /************************************************
    * Spark::TagPool
    ***********************************************/

    SPARK_API class TagPool{
    private:
        EntityList m_pool;
    public:
        void AddEntity(Entity* entity);
        void RemoveEntity(Entity* entity);
        bool ContainsEntity(Entity* entity);
        const EntityList& GetEntityList();
    };

    /************************************************
    * Spark::Scene
    ***********************************************/

    SPARK_API class Scene{
    private:
        EntityList                  m_entities;
        EntityList                  m_destroyedEntites;
        StringCount                 m_entityNames;
        StringMap<TagPool*>         m_entityTags;
        TypeMap<System*>            m_systems;
        TypeMap<IComponentPool*>    m_pools;

    public:
        Scene();
        ~Scene();

        void    StartFrame();
        Entity* CreateEntity(const std::string& name = "");
        Entity* GetEntityByName(const std::string& name);
        const   EntityList& GetEntityListByTag(const std::string& tag);
        void    TagEntity(Entity* entity, const std::string& tag);
        void    DestroyEntity(Entity* entity);
        void    Update();
        void    Render(Renderer* renderer);

        template<typename T>
        void RegisterSystem();

        template<typename T>
        T* GetSystem();

        template<typename T, typename ...TArgs>
        T* AddComponent(Entity* entity, TArgs&& ...args);

        template<typename T>
        T* GetComponent(Entity *entity);

        template<typename T>
        bool HasComponent(Entity *entity);

        template<typename T>
        void RemoveComponent(Entity *entity);
    };

    /************************************************
    * Spark::Entity Template Implementation
    ***********************************************/

    template<typename T, typename ...TArgs>
    T* Entity::AddComponent(TArgs&& ...args){
        return m_scene->AddComponent<T>(this, std::forward<TArgs>(args)...);
    }

    template<typename T>
    T* Entity::GetComponent(){
        return m_scene->GetComponent<T>(this);
    }

    template<typename T>
    bool Entity::HasComponent(){
        return m_scene->HasComponent<T>(this);
    }

    template<typename T>
    void Entity::RemoveComponent(){
         m_scene->RemoveComponent<T>(this);
    }

    /************************************************
    * Spark::System Template Implementation
    ***********************************************/
    template<typename T>
    void System::RequireComponent(){
        UUID componentID = Component<T>::GetID();
        m_signature.Set(componentID);
    }

    /************************************************
    * Spark::Scene Template Implementation
    ***********************************************/
    template<typename T>
    void Scene::RegisterSystem(){
        auto it = m_systems.find(typeid(T));
        if (it != m_systems.end())
            return;

        auto* system = static_cast<System*>(new T());
        system->SetScene(this);
        system->Setup();
        m_systems.emplace(typeid(T), system);
    }

    template<typename T>
    T* Scene::GetSystem(){
        auto it = m_systems.find(typeid(T));
        if (it == m_systems.end())
            return nullptr;
        return static_cast<T*>(it->second);
    }

    template<typename T, typename ...TArgs>
    T* Scene::AddComponent(Entity* entity, TArgs&& ...args){
        UUID componentID = Component<T>::GetID();

        if (entity->signature.Test(componentID)){
            return nullptr;
        }
        auto it = m_pools.find(typeid(T));
        ComponentPool<T>* pool;

        if (it == m_pools.end()){
            pool = new ComponentPool<T>();
            m_pools.emplace(typeid(T), static_cast<IComponentPool*>(pool));
        } else{
            pool = static_cast<ComponentPool<T>*>(it->second);
        }

        auto *component = new T(std::forward<TArgs>(args)...);
        pool->Register(entity, component);
        entity->signature.Set(componentID);

        for (auto& el: m_systems){
            System* system = el.second;
            if(system->BelongsToSystem(entity)){
                system->AddToSystem(entity);
            }
        }

        return component;
    }

    template<typename T>
    T* Scene::GetComponent(Entity *entity){
        auto it = m_pools.find(typeid(T));
        if (it == m_pools.end())
            return nullptr;

        auto* pool = static_cast<ComponentPool<T>*>(it->second);
        return pool->Get(entity);
    }


    template<typename T>
    bool Scene::HasComponent(Entity *entity){
        auto it = m_pools.find(typeid(T));

        if (it == m_pools.end())
            return false;

        return it->second->HasEntity(entity);
    }

    template<typename T>
    void Scene::RemoveComponent(Entity *entity){
        auto it = m_pools.find(typeid(T));

        if (it == m_pools.end())
            return;

        UUID componentID = Component<T>::GetID();
        it->second->Remove(entity);
        entity->signature.Clear(componentID);

        for(auto& el: m_systems){
            el.second->RemoveFromSystem(entity);
        }
    }
}

#endif //SPARK_ENGINE_ECS_H
