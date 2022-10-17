#ifndef COMPONENT_H
#define COMPONENT_H

#include "Renderer/Mesh.h"
#include "Scene/Components/Terrain.h"


#include <string>

#include <glm/glm.hpp>


namespace ENGINE
{

struct TagComponent
{
    std::string Tag;

    TagComponent() = default;
    TagComponent(const TagComponent&) = default;
    TagComponent(const std::string & tag)
        : Tag(tag) {}
};

struct TransformComponent
{
    glm::mat4 Transform;

    TransformComponent() = default;
    TransformComponent(const TransformComponent&) = default;
    TransformComponent(const glm::mat4& transform)
        : Transform(transform) {}

    operator glm::mat4& () { return Transform; }
    operator const glm::mat4& () const { return Transform; }
};

struct PositionComponent
{
    glm::vec3 Position;
    glm::vec4 Rotation = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
    // glm::vec4 Rotation = glm::vec4(0.0001f, 0.0001f, 0.0001f, 0.0f);

    PositionComponent() = default;
    PositionComponent(const PositionComponent&) = default;
    PositionComponent(const glm::vec3& position)
        : Position(position)
    {}
    PositionComponent(
        const glm::vec3& position,
        const glm::vec4& rotation)
        : Position(position)
        , Rotation(rotation)
    {}
};

struct SpeedComponent
{
    float Speed = 2.5f;

    SpeedComponent() = default;
    SpeedComponent(const SpeedComponent&) = default;
    SpeedComponent(const float speed)
        : Speed(speed) {}
};

struct MeshComponent
{
    Mesh mesh;

    MeshComponent() = default;
    MeshComponent(const MeshComponent&) = default;
    MeshComponent(const Mesh& meshData)
        : mesh(meshData) {}
};

struct TerrainComponent
{
    Terrain terrain;

    TerrainComponent() = default;
    TerrainComponent(const TerrainComponent&) = default;
    TerrainComponent(const Terrain& terrainData)
        : terrain(terrainData) {}
};


}

#endif // COMPONENT_H