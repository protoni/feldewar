#include "Input.h"
#include "Scene/Entity.h"
#include "DebugMacros.h"
#include "EngineUtils.h"

#include <iostream>



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

void Input::setKeyPressed(INPUT_EVENTS key)
{
    m_inputEvents |= static_cast<int>(key);
}

const bool Input::KeyPressed(const INPUT_EVENTS& key) const
{
    return m_inputEvents & static_cast<int>(key);
}

void Input::processInput(double deltaTime)
{
    m_debounceCounter += deltaTime;

    // Get new events
    glfwPollEvents();

    // Clear input
    m_inputEvents = 0;

    // Handle exit input
    if (glfwGetKey(m_window->get(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(m_window->get(), true);

    
    // Handle camera movement input
    const float cameraSpeed = 2.5f * (float)deltaTime;
    
    if (glfwGetKey(m_window->get(), GLFW_KEY_W) == GLFW_PRESS) {
        if(m_window->GetDebugMode())
            m_camera->ProcessKeyboard(CameraMovement::FORWARD, deltaTime);
        setKeyPressed(INPUT_EVENTS::INPUT_EVENT_W);
    }
    if (glfwGetKey(m_window->get(), GLFW_KEY_S) == GLFW_PRESS) {
        if(m_window->GetDebugMode())
            m_camera->ProcessKeyboard(CameraMovement::BACKWARD, deltaTime);
        setKeyPressed(INPUT_EVENTS::INPUT_EVENT_S);
    }
    if (glfwGetKey(m_window->get(), GLFW_KEY_A) == GLFW_PRESS) {
        if(m_window->GetDebugMode())
            m_camera->ProcessKeyboard(CameraMovement::LEFT, deltaTime);
        setKeyPressed(INPUT_EVENTS::INPUT_EVENT_A);
    }
    if (glfwGetKey(m_window->get(), GLFW_KEY_D) == GLFW_PRESS) {
        if(m_window->GetDebugMode())
            m_camera->ProcessKeyboard(CameraMovement::RIGHT, deltaTime);
        setKeyPressed(INPUT_EVENTS::INPUT_EVENT_D);
    }
    if (glfwGetKey(m_window->get(), GLFW_KEY_SPACE) == GLFW_PRESS) {
        if(m_window->GetDebugMode())
            m_camera->ProcessKeyboard(CameraMovement::UP, deltaTime);
        setKeyPressed(INPUT_EVENTS::INPUT_EVENT_SPACE);
    }
    if (glfwGetKey(m_window->get(), GLFW_KEY_X) == GLFW_PRESS) {
        if(m_window->GetDebugMode())
            m_camera->ProcessKeyboard(CameraMovement::DOWN, deltaTime);
        setKeyPressed(INPUT_EVENTS::INPUT_EVENT_X);
    }

    UTILS::PrintVec(m_camera->Position, "Camera pos");
    
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

}


} // namespace ENGINE


