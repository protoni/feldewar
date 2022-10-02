#include "Application.h"
#include "DebugMacros.h"

#include <chrono>
#include <thread>

namespace ENGINE
{

Application::Application()
{
}

Application::~Application()
{
}

const bool Application::Init(WindowSettings& settings, Error& error)
{
    // Create camera
    m_camera = std::make_shared<Camera>();
    if (!m_camera) {
        error.Set(ErrorMessage::CameraCreationError);
        return false;
    }
    m_camera->setWindowSize(settings.width, settings.height);


    // Create new window
    m_window = std::make_shared<Window>(settings, m_camera);
    if (!m_window || !m_window->init()) {
        error.Set(ErrorMessage::WindowCreationError);
        return false;
    }

    // Init input
    m_input = std::make_unique<Input>(m_window, m_camera);// , debugUi, scene);
    if (!m_input) {
        error.Set(ErrorMessage::InputCreationError);
        return false;
    }
}

void Application::ProcessInput()
{
    m_input->processInput(m_deltaTime);
}

bool Application::Run()
{
    // Calculate delta time
    double currentFrame = glfwGetTime();
    m_deltaTime = currentFrame - m_lastFrame;
    m_lastFrame = currentFrame;

    // Limit FPS
    m_sleep_time = m_frame_time - (m_deltaTime * 1000);
    std::this_thread::sleep_for(std::chrono::microseconds(static_cast<int>(m_sleep_time)));

    // Clear background
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 120fps -> 130fps

    // Update frame counter
    m_secondFrame += m_deltaTime;
    m_fpsCounter++;

    // Do something every second
    if (m_secondFrame >= 1.0f) {
        m_secondFrame = 0.0f;

        // Print out FPS and delta time
        std::cout << "deltaTime: " << m_deltaTime << std::endl;
        std::cout << "FPS: " << m_fpsCounter << std::endl;
        m_fps = m_fpsCounter;
        m_fpsCounter = 0.0f;
    }

    m_window->swapBuffers();

    return !m_window->shouldExit();
}

void Application::Cleanup()
{
    m_window->Cleanup();
}

} // namespace ENGINE