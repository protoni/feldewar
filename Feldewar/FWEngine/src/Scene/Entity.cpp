#include "Entity.h"

namespace ENGINE
{

Entity::Entity(entt::entity handle, Scene* scene)
    : m_entityHandle(handle), m_scene(scene)
{
}

Entity::~Entity()
{
}

// Moving
const bool Entity::Move(const glm::vec3& pos)
{
    if (HasComponent<PositionComponent>()) {
        auto& position = GetComponent<PositionComponent>();
        position.Position += pos;
        return true;
    }

    return false;
}

const bool Entity::MoveLeft(const float amount) {
    return(Move(glm::vec3(-amount, 0.0f, 0.0f)));
}

const bool Entity::MoveRight(const float amount) {
    return(Move(glm::vec3(amount, 0.0f, 0.0f)));
}

const bool Entity::MoveUp(const float amount) {
    return(Move(glm::vec3(0.0f, amount, 0.0f)));
}

const bool Entity::MoveDown(const float amount) {
    return(Move(glm::vec3(0.0f, -amount, 0.0f)));
}


}
