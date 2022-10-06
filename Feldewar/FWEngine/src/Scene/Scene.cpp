#include "Scene.h"
#include "Component.h"
#include "Entity.h"
#include "Renderer/Renderer.h"
#include "Primitives.h"

#include <iostream>

namespace ENGINE
{

static void onTransfromConstruct(entt::registry& registry, entt::entity entity)
{
    std::cout << "Entity created: " << static_cast<int>(entity) << std::endl;
    
    //if (entityObj.HasComponent<TagComponent>()) {
    //    auto view = registry.view<TagComponent>();
    //    TagComponent tag = view.get<TagComponent>(entity);
    //}
}

Scene::Scene(std::shared_ptr<Renderer>& renderer) : m_renderer(renderer)
{
    std::cout << "Scene constructed!" << std::endl;
    
}

Scene::~Scene()
{
    
}

Entity Scene::CreateEntity(const std::string& name)
{
    m_registry.on_construct<TransformComponent>().connect<&onTransfromConstruct>();

    Entity entity = { m_registry.create(), this };
    entity.AddComponent<TransformComponent>(glm::mat4(1.0f));
    entity.AddComponent<MeshComponent>(Rectangle());
    
    auto& tag = entity.AddComponent<TagComponent>();
    tag.Tag = name.empty() ? "Entity" : name;

    return entity;
}

const bool Scene::Update() const
{
    //auto view = m_registry.view<TransformComponent>();
    //for (auto entity : view) {
    //    TransformComponent& item = view.get<TransformComponent>(entity);
    //}

    for (auto [entity, position, transformation, tag, meshData] :
        m_registry.view<PositionComponent, TransformComponent, TagComponent, MeshComponent>().each()) {

        std::cout << "\n----------------------------------------------" << std::endl;
        std::cout << "Entity ID: " << static_cast<int>(entity) << std::endl;
        std::cout << "Position:  " << position.Position.x << std::endl;
        std::cout << "Tag:       " << tag.Tag << std::endl;
        std::cout << "----------------------------------------------\n" << std::endl;

        m_renderer->DrawRect(
            transformation.Transform,
            position.Position,
            meshData.mesh
        );
    }

    return false;
}

}