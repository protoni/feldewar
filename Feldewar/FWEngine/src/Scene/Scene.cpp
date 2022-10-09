#include "Scene.h"
#include "Component.h"
#include "Entity.h"
#include "Renderer/Renderer.h"
#include "Primitives.h"


#include <iostream>
#include <memory>

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
    
    // Load terrain texture
    m_terrainTexture = DataLoader::GetTexture("grass.png");//new Texture(texture, true);

    // Load terrain height map
    m_terrainHeightMap = DataLoader::GetTexture("heightmap.png");//new Texture(heightmap, true);

}

Scene::~Scene()
{
    
}

Entity Scene::CreateEntity(const std::string& name)
{
    m_registry.on_construct<TransformComponent>().connect<&onTransfromConstruct>();

    Entity entity = { m_registry.create(), this };
    entity.AddComponent<TransformComponent>(glm::mat4(1.0f));
    
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

    // Draw terrain first
    for (auto [entity, transformation, position, terrainData] :
        m_registry.view<TransformComponent, PositionComponent, TerrainComponent>().each()) {

        std::cout << "\n------------------TERRAIN --------------------" << std::endl;
        std::cout << "Entity ID: " << static_cast<int>(entity) << std::endl;
        std::cout << "----------------------------------------------\n" << std::endl;

        std::cout << " Terrain vertex count: " << terrainData.terrain.GetVertexCount() << std::endl;
        m_renderer->DrawTerrain(transformation.Transform, position.Position, terrainData.terrain);
    }

    for (auto [entity, position, transformation, tag, meshData] :
        m_registry.view<PositionComponent, TransformComponent, TagComponent, MeshComponent>().each()) {

            std::cout << "\n------------------OBJECTS---------------------" << std::endl;
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

Entity Scene::AddRectangle2D(const std::string& name)
{
    Entity entity = CreateEntity(name);
    entity.AddComponent<PositionComponent>(glm::vec3(0.0f, 0.0f, 0.0f));

    PRIMITIVES::Rectangle2D rect = PRIMITIVES::Rectangle2D();
    //rect.SetEntityHandle(entity);

    entity.AddComponent<MeshComponent>(rect);

    return entity;
}

Entity Scene::AddTerrain(const TerrainSettings& settings)
{
    Entity entity = CreateEntity("Terrain");
    entity.AddComponent<PositionComponent>(glm::vec3(0.0f, 0.0f, 0.0f));

    //std::shared_ptr<Terrain> terrain = std::make_shared<Terrain>(0, 0, settings.texture.c_str(), settings.heightMap.c_str());
    
    //Terrain terrain = Terrain(0, 0, settings.texture.c_str(), settings.heightMap.c_str());
    Terrain terrain = Terrain(
        0,
        0,
        DataLoader::GetTexture(settings.texture.c_str()),
        DataLoader::GetTexture(settings.heightMap.c_str())
    );

    entity.AddComponent<TerrainComponent>(terrain);

    return entity;
}

}