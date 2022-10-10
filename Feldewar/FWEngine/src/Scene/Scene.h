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

class Application;
class Renderer;
class Entity;

class Scene
{
public:
    Scene(std::shared_ptr<Renderer>& renderer, Application* app);
    ~Scene();

    // Update and draw the scene
    const bool Update() const;

    // Base method for creating entities
    Entity CreateEntity(const std::string& name = std::string());

    // Add 2D rectangle primitive
    Entity AddRectangle2D(const std::string& name = std::string());

    // Add 3D cube primitive
    Entity AddCube3D(const std::string& name = std::string());

    // Load terrain related data
    Entity AddTerrain(const TerrainSettings& settings);

    // Add player entity
    Entity AddPlayer(Entity& entity, const std::string& name = std::string());

    // Does the scene have player object
    //const bool HasPlayer() const { return m_player ? true : false; }

    // Return player entity
    //Entity GetPlayer();// { return m_player; }

private:

    // Save main application instance here
    Application* m_app;

    std::shared_ptr<Renderer> m_renderer;

    friend class Entity;
    entt::registry m_registry;

    // Textures
    Texture m_terrainTexture;
    Texture m_terrainHeightMap;

    // Main player entity
    //Entity m_player;
};

} // namespace ENGINE

#endif // SCENE_H