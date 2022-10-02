#include "Scene.h"
#include "Component.h"
#include "Entity.h"

//#include <dependencies/glm/glm.hpp>

namespace ENGINE
{

Scene::Scene()
{
    

    //entt::entity entity = m_registry.create();
    //m_registry.emplace<TransformComponent>(entity, glm::mat4(1.0f));
}

Scene::~Scene()
{

}

Entity Scene::CreateEntity(const std::string& name)
{
    Entity entity = { m_registry.create(), this };
    entity.AddComponent<TransformComponent>();
    auto& tag = entity.AddComponent<TagComponent>();

    tag.Tag = name.empty() ? "Entity" : name;

    return { m_registry.create(), this };
}

}