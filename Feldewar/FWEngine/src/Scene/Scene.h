#ifndef SCENE_H
#define SCENE_H

#include "Settings.h"
#include "Error.h"
#include "DataObjects/Texture.h"
#include "DataObjects/DataLoader.h"

#include <string>

#include <entt/entt.hpp>

namespace ENGINE
{

class Renderer;
class Entity;

class Scene
{
public:
    Scene(std::shared_ptr<Renderer>& renderer);
    ~Scene();

    Entity CreateEntity(const std::string& name = std::string());

    const bool Update() const;

    // Add 2D rectangle primitive
    Entity AddRectangle2D(const std::string& name = std::string());

    // Add 3D cube primitive
    Entity AddCube3D(const std::string& name = std::string());

    // Load terrain related data
    Entity AddTerrain(const TerrainSettings& settings);

private:
    std::shared_ptr<Renderer> m_renderer;

    friend class Entity;
    entt::registry m_registry;

    // Textures
    Texture m_terrainTexture;
    Texture m_terrainHeightMap;
    

};

} // namespace ENGINE

#endif // SCENE_H