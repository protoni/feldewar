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

void Input::processInput(double deltaTime)
{
    m_debounceCounter += deltaTime;

    // Handle exit input
    if (glfwGetKey(m_window->get(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(m_window->get(), true);

    
    // Handle camera movement input
    const float cameraSpeed = 2.5f * (float)deltaTime;
    
    if (glfwGetKey(m_window->get(), GLFW_KEY_W) == GLFW_PRESS) {
        m_camera->ProcessKeyboard(CameraMovement::FORWARD, deltaTime);
    }
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

    UTILS::PrintVec(m_camera->Position, "Camera pos");
    
    if (!m_window->GetDebugMode()) {
        if (m_scene && m_player) {
            const float velocity = m_player->GetSpeed() * (float)deltaTime;

            //glm

            //m_player->MoveTo(m_camera->Front + 2.0f);
            //std::cout << "Moving player with velocity: " << velocity << std::endl;
            //std::cout << "Player speed: " << m_player->GetSpeed() << std::endl;
            //if (glfwGetKey(m_window->get(), GLFW_KEY_W) == GLFW_PRESS) {
            //    m_player->MoveForward(velocity);
            //    //std::cout << "Moving forward!" << std::endl;
            //}
            //if (glfwGetKey(m_window->get(), GLFW_KEY_S) == GLFW_PRESS)
            //    m_player->MoveBackward(velocity);
            //if (glfwGetKey(m_window->get(), GLFW_KEY_A) == GLFW_PRESS)
            //    m_player->MoveLeft(velocity);
            //if (glfwGetKey(m_window->get(), GLFW_KEY_D) == GLFW_PRESS)
            //    m_player->MoveRight(velocity);

            //m_player->MoveTo(m_camera->Position + (m_camera->Front* velocity));

            //const glm::vec3& pos = m_player->GetPosition();
            //UTILS::PrintVec(m_player->GetPosition());
            //std::cout << "Player pos: [ " << pos.x << ", " << pos.y << ", " << pos.z << " ]" << std::endl;
            //m_camera->Follow(m_player->GetPosition());
        }
    }
    //else {
    //    // Handle player movement
    //    //Entity player = m_scene->GetPlayer();
    //
    //    if (m_scene && m_player) {
    //        //Entity player = m_scene->GetPlayer();
    //        float velocity = m_player->GetSpeed() * (float)deltaTime;
    //
    //        if (glfwGetKey(m_window->get(), GLFW_KEY_W) == GLFW_PRESS)
    //            m_player->MoveForward(velocity);
    //        else if (glfwGetKey(m_window->get(), GLFW_KEY_S) == GLFW_PRESS)
    //            m_player->MoveBackward(velocity);
    //        if (glfwGetKey(m_window->get(), GLFW_KEY_A) == GLFW_PRESS)
    //            m_player->MoveLeft(velocity);
    //        if (glfwGetKey(m_window->get(), GLFW_KEY_D) == GLFW_PRESS)
    //            m_player->MoveRight(velocity);
    //
    //        m_camera->Follow(m_player->GetPosition());
    //    }
    //    
    //
    //}

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


