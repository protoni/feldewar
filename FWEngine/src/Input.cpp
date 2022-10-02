#include "Input.h"
#include <iostream>

#include "DebugMacros.h"

namespace ENGINE
{

Input::Input(std::shared_ptr<Window> window, std::shared_ptr<Camera> camera) : //, DebugUi* debugUi, Scene* scene) :
    m_window(window), m_camera(camera), //m_debugUi(debugUi),
    m_debounceCounter(0)//, m_scene(scene)
{

}

Input::~Input()
{
}

void Input::processInput(double deltaTime)
{
    m_debounceCounter += deltaTime;

    // Handle exit input
    if (glfwGetKey(m_window->get(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(m_window->get(), true);

    // Handle camera movement input
    const float cameraSpeed = 2.5f * (float)deltaTime;
    if (glfwGetKey(m_window->get(), GLFW_KEY_W) == GLFW_PRESS)
        m_camera->ProcessKeyboard(CameraMovement::FORWARD, deltaTime);
    if (glfwGetKey(m_window->get(), GLFW_KEY_S) == GLFW_PRESS)
        m_camera->ProcessKeyboard(CameraMovement::BACKWARD, deltaTime);
    if (glfwGetKey(m_window->get(), GLFW_KEY_A) == GLFW_PRESS)
        m_camera->ProcessKeyboard(CameraMovement::LEFT, deltaTime);
    if (glfwGetKey(m_window->get(), GLFW_KEY_D) == GLFW_PRESS)
        m_camera->ProcessKeyboard(CameraMovement::RIGHT, deltaTime);
    if (glfwGetKey(m_window->get(), GLFW_KEY_SPACE) == GLFW_PRESS)
        m_camera->ProcessKeyboard(CameraMovement::UP, deltaTime);
    if (glfwGetKey(m_window->get(), GLFW_KEY_X) == GLFW_PRESS)
        m_camera->ProcessKeyboard(CameraMovement::DOWN, deltaTime);

    bool changed = false;

    // Limit actions to 50ms
    if (m_debounceCounter >= .05) {
        
    }

    // Limit actions to 500ms
    if (m_debounceCounter >= .5) {

        // Toggle debug UI
        if (glfwGetKey(m_window->get(), GLFW_KEY_TAB) == GLFW_PRESS) {

            m_window->debugMode();
            //m_debugUi->debugMode();
            std::cout << "dbg mode!" << std::endl;
            changed = true;
        }
    }

    if (changed)
        m_debounceCounter = 0;

    glfwPollEvents();
}

} // namespace ENGINE


