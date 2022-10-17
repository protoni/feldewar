#ifndef INPUT_H
#define INPUT_H

#include "Camera.h"
#include "Window.h"
//#include "DebugUi.h"
#include "Scene.h"

#include <memory>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace ENGINE
{

typedef unsigned long long InputEvent;
//unsigned long long MovementInput;

enum class INPUT_EVENTS
{
    INPUT_EVENT_NONE  = 0,
    INPUT_EVENT_W     = 1 << 0,
    INPUT_EVENT_A     = 1 << 1,
    INPUT_EVENT_S     = 1 << 2,
    INPUT_EVENT_D     = 1 << 3,
    INPUT_EVENT_SPACE = 1 << 4,
    INPUT_EVENT_X     = 1 << 5
};


class Input
{
public:

    Input(std::shared_ptr<Window> window, std::shared_ptr<Camera> camera); // , DebugUi* debugUi, Scene* scene);
    ~Input();

    void processInput(double deltaTime);

    void SetScene(std::shared_ptr<Scene>& scene) { m_scene = scene; }
    void SetPlayer(Entity* player) { m_player = player; }

    // Check keyboard event
    const bool KeyPressed(const INPUT_EVENTS& key) const;

private:
    void setKeyPressed(INPUT_EVENTS key);

    std::shared_ptr<Window> m_window = nullptr;
    std::shared_ptr<Camera> m_camera = nullptr;
    std::shared_ptr<Scene>  m_scene  = nullptr;
    Entity* m_player = nullptr;
    //DebugUi* m_debugUi;
    //Scene* m_scene;

    double m_debounceCounter;

    // Keyboard events during last frame
    InputEvent m_inputEvents;

};

}

#endif // INPUT_H