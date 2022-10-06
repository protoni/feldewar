#ifndef COMPONENT_H
#define COMPONENT_H

#include "Mesh.h"

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

    PositionComponent() = default;
    PositionComponent(const PositionComponent&) = default;
    PositionComponent(const glm::vec3& position)
        : Position(position) {}
};

struct MeshComponent
{
    Mesh mesh;

    MeshComponent() = default;
    MeshComponent(const MeshComponent&) = default;
    MeshComponent(const Mesh& meshData)
        : mesh(meshData) {}
};

}

#endif // COMPONENT_H