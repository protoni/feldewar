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

}
