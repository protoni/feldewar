#ifndef ENTITY_H
#define ENTITY_H
//#include "../FWEngine.h"
#include "Scene.h"

#include <entt/entt.hpp>

namespace ENGINE
{
//class Scene;
class Entity
{
public:
    //Entity() = default;
    Entity(entt::entity handle, Scene* scene);
    ~Entity();

    template<typename T, typename... Args>
    T& AddComponent(Args&&... args)
    {
        //assert(!HasComponent<T>());
        return m_scene->m_registry.emplace<T>(m_entityHandle, std::forward<Args>(args)...);
    }

    template<typename T>
    T& GetComponent()
    {
        //assert(!HasComponent<T>());
        return m_scene->m_registry.get<T>(m_entityHandle);
    }

    template<typename T>
    bool HasComponent()
    {
        return m_scene->m_registry.any_of<T>(m_entityHandle);
    }

    template<typename T>
    void RemoveComponent()
    {
        m_scene->m_registry.remove<T>(m_entityHandle);
    }

    operator bool() const { return m_entityHandle != entt::null; }

private:
    entt::entity m_entityHandle{ entt::null };
    Scene* m_scene = nullptr;
};

}

#endif // ENTITY_H