#ifndef ENTITY_H
#define ENTITY_H
//#include "../FWEngine.h"
#include "Scene.h"
#include "Renderer/Mesh.h"
#include "Component.h"

#include <entt/entt.hpp>
#include <glm/glm.hpp>

namespace ENGINE
{
//class Scene;
class Entity
{
public:
    Entity() = default;
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

    // Moving
    const bool Move(const glm::vec3& pos);
    const bool MoveTo(const glm::vec3& pos);
    const bool MoveLeft(const float amount);
    const bool MoveRight(const float amount);
    const bool MoveUp(const float amount);
    const bool MoveDown(const float amount);
    const bool MoveForward(const float amount);
    const bool MoveBackward(const float amount);

    // Rotation
    const bool Rotate(const glm::vec3& rotation);    // Add to current rotation of all axis' a specific amount
    const bool RotateTo(const glm::vec3& rotation);  // Rotate all axis to a specific value
    const bool RotateHorizontal(const float amount); // Rotate around Y-axis
    const bool RotateVertical(const float amount);   // Rotate around X-axis
    const bool RotateLeft(const float amount);       // Rotate around Y-axis to left
    const bool RotateRight(const float amount);      // Rotate around Y-axis to right

    // Get entity position
    const glm::vec3& GetPosition();

    // Get entity mesh if it exists
    const bool GetMesh(Mesh& mesh);

    // Get speed of a entity if speed component exists
    const float GetSpeed();

    //const entt::entity GetHandle() const { return m_entityHandle; }

    operator bool() const { return m_entityHandle != entt::null; }

private:
    entt::entity m_entityHandle{ entt::null };
    Scene* m_scene = nullptr;
};

}

#endif // ENTITY_H