#ifndef SCENE_H
#define SCENE_H

#include "entt.hpp"

namespace ENGINE
{

class Scene
{

public:
    Scene();
    ~Scene();

private:
    entt::registry m_registry;

};

} // namespace ENGINE

#endif // SCENE_H