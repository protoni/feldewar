#include "Entity.h"
#include "EngineUtils.h"

namespace ENGINE
{

Entity::Entity(entt::entity handle, Scene* scene)
    : m_entityHandle(handle), m_scene(scene)
{
}

Entity::~Entity()
{
}

const bool Entity::Move(const glm::vec3& pos)
{
    if (HasComponent<PositionComponent>()) {
        auto& position = GetComponent<PositionComponent>();
        position.Position += pos;
        return true;
    }

    return false;
}

const bool Entity::MoveTo(const glm::vec3& pos)
{
    if (HasComponent<PositionComponent>()) {
        auto& position = GetComponent<PositionComponent>();
        position.Position = pos;
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

const bool Entity::MoveForward(const float amount) {
    return(Move(glm::vec3(0.0f, 0.0f, -amount)));
}

const bool Entity::MoveBackward(const float amount) {
    return(Move(glm::vec3(0.0f, 0.0f, amount)));
}

const bool Entity::Rotate(const glm::vec3& rotation)
{
    if (HasComponent<PositionComponent>()) {
        auto& position = GetComponent<PositionComponent>();

        (position.Rotation.x + rotation.x) > 360.0f ? position.Rotation.x -= 360.0f : 0;
        (position.Rotation.x + rotation.x) <   0.0f ? position.Rotation.x += 360.0f : 0;

        (position.Rotation.y + rotation.y) > 360.0f ? position.Rotation.y -= 360.0f : 0;
        (position.Rotation.y + rotation.y) <   0.0f ? position.Rotation.y += 360.0f : 0;

        (position.Rotation.z + rotation.z) > 360.0f ? position.Rotation.z -= 360.0f : 0;
        (position.Rotation.z + rotation.z) <   0.0f ? position.Rotation.z += 360.0f : 0;

        position.Rotation += glm::vec4(rotation, 0.0f);
        return true;
    }

    return false;
}

const bool Entity::RotateTo(const glm::vec3& rotation)
{
    if (HasComponent<PositionComponent>()) {
        auto& position = GetComponent<PositionComponent>();
        glm::vec3 newRotation = glm::vec3();

        position.Rotation = glm::vec4(rotation, 0.0f);
        return true;
    }

    return false;
}

const bool Entity::RotateHorizontal(const float amount)
{
    return(Rotate(glm::vec3(0.0f, amount, 0.0f)));
}

const bool Entity::RotateVertical(const float amount)
{
    return(Rotate(glm::vec3(amount, 0.0f, 0.0f)));
}

const bool Entity::RotateLeft(const float amount)
{
    return(Rotate(glm::vec3(0.0f, amount, 0.0f)));
}

const bool Entity::RotateRight(const float amount)
{
    return(Rotate(glm::vec3(0.0f, -amount, 0.0f)));
}

const glm::vec3& Entity::GetPosition()
{
    if (HasComponent<PositionComponent>()) {
        auto& position = GetComponent<PositionComponent>();
        return position.Position;
    }

    return glm::vec3(0.0f);
}

const bool Entity::GetMesh(Mesh& mesh)
{
    if (HasComponent<MeshComponent>()) {
        auto& meshComponent = GetComponent<MeshComponent>();
        mesh = meshComponent.mesh;
        return true;
    }

    return false;
}

const float Entity::GetSpeed()
{
    if (HasComponent<SpeedComponent>()) {
        auto& speedComponent = GetComponent<SpeedComponent>();
        return speedComponent.Speed;
    }

    return 0.0f;
}

}
