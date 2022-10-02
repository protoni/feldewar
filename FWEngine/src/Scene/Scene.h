#ifndef SCENE_H
#define SCENE_H

//#include "../FWEngine.h"

#include <string>

#include <dependencies/entt/entt.hpp>

namespace ENGINE
{

class Entity;
class Scene
{

//class Entity;

public:
    Scene();
    ~Scene();

    Entity CreateEntity(const std::string& name = std::string());

private:
    friend class Entity;
    entt::registry m_registry;
    

};

} // namespace ENGINE

#endif // SCENE_H