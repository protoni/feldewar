#ifndef COMPONENT_H
#define COMPONENT_H

#include <glm/glm.hpp>

namespace ENGINE
{

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

}

#endif // COMPONENT_H