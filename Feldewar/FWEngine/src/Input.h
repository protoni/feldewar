#ifndef INPUT_H
#define INPUT_H

#include "Camera.h"
#include "Window.h"
//#include "DebugUi.h"
//#include "Scene.h"

#include <memory>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace ENGINE
{

class Input
{
public:

    Input(std::shared_ptr<Window> window, std::shared_ptr<Camera> camera); // , DebugUi* debugUi, Scene* scene);
    ~Input();

    void processInput(double deltaTime);

private:
    std::shared_ptr<Window> m_window = nullptr;
    std::shared_ptr<Camera> m_camera = nullptr;
    //DebugUi* m_debugUi;
    //Scene* m_scene;

    double m_debounceCounter;

};

}

#endif // INPUT_H