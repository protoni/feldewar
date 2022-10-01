#include "Scene.h"
#include "Component.h"

#include <glm/glm.hpp>

namespace ENGINE
{

Scene::Scene()
{
    

    entt::entity entity = m_registry.create();
    m_registry.emplace<TransformComponent>(entity, glm::mat4(1.0f));
}

Scene::~Scene()
{

}

}