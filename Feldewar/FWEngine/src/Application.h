#ifndef APPLICATION_H
#define APPLICATION_H

#include "Error.h"
#include "Settings.h"
#include "Window.h"
#include "Camera.h"
#include "Input.h"
#include "Scene/Scene.h"
#include "Scene/Components/Player.h"
#include "Renderer/Renderer.h"

#include <memory>


namespace ENGINE
{

class Application
{
public:
    Application();
    ~Application();

    // Init window, camera and input stuff
    const bool Init(WindowSettings& settings, Error& error);

    // Load textures, models and shaders
    static const bool LoadData(DataSettings& settings, Error& error);

    // Handle input
    void ProcessInput();

    // Add new scene
    Scene& CreateScene(Error& error);

    // Get renderer object
    Renderer& GetRenderer();

    // Set main player when created
    //void SetPlayer(std::shared_ptr<Entity>& player);
    void SetPlayer(Entity* player);

    // Run main appilcation loop
    bool Run();

    // Cleanup objects, any data and GLFW
    void Cleanup();

private:
    std::shared_ptr<Window>    m_window   = nullptr;
    std::unique_ptr<Input>     m_input    = nullptr;
    std::shared_ptr<Camera>    m_camera   = nullptr;
    std::shared_ptr<Scene>     m_scene    = nullptr;
    std::shared_ptr<Renderer>  m_renderer = nullptr;

    Entity* m_player = nullptr;

    // Time
    double m_deltaTime = 0.0f;   // Time between current frame and last frame
    double m_lastFrame = 0.0f;   // Time of last frame
    double m_secondFrame = 0.0f; // Count seconds
    double m_fpsCounter = 0.0f;  // Count frames per second
    double m_fpsLimit = 120.0f;   // MAX FPS
    double m_frame_time = (1.0f / m_fpsLimit) * 1000;
    double m_sleep_time = 0.0f;
    double m_fps = 0.0f;

    // Has the application been initialized
    bool m_initialized = false;

};
} // namespace ENGINE

#endif // APPLICATION_H