#include "Window.h"

#include <iostream>

#include "DebugMacros.h"

namespace ENGINE
{

Window::Window(WindowSettings& settings, std::shared_ptr<Camera> camera) :
    m_windowSettings(settings), m_firstMouse(true), m_camera(camera),
    m_lastX(settings.width / 2.0), m_lastY(settings.height / 2.0),
    m_debugModeOn(false), m_wireframeModeOn(false)
{

}

Window::~Window()
{

}

bool Window::init()
{
    std::cout << "Init OpenGLRenderer" << std::endl;

    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // Create a window
    m_window = glfwCreateWindow(m_windowSettings.width, m_windowSettings.height, m_windowSettings.name.c_str(), NULL, NULL);
    if (m_window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return false;
    }
    glfwMakeContextCurrent(m_window);

    // Init GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD!" << std::endl;
        return false;
    }

    // Set window viewport dimensions
    glViewport(0, 0, m_windowSettings.width, m_windowSettings.height);

    // Set window resize callback
    glfwSetFramebufferSizeCallback(m_window, framebufferSizeCallback);

    // Disable cursor
    glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Set mouse input callback
    glfwSetCursorPosCallback(m_window, mouseCallback);

    // Set mouse scroll callback
    glfwSetScrollCallback(m_window, scrollCallback);

    // Set pointer to this object
    glfwSetWindowUserPointer(m_window, this);

    return true;
}

//void Window::setCamera(Camera* camera)
//{
//    m_camera = camera;
//
//    // Init windows size for camera
//    m_camera->setWindowSize(m_windowSettings->width, m_windowSettings->height);
//}

void Window::mouseCallback(GLFWwindow* window, double xposIn, double yposIn)
{
    Window* windowObject = static_cast<Window*>(glfwGetWindowUserPointer(window));

    // Save old mouse position
    windowObject->m_mousePosX = static_cast<float>(xposIn);
    windowObject->m_mousePosY = static_cast<float>(yposIn);
    windowObject->m_camera->setMousePos(static_cast<float>(xposIn), static_cast<float>(yposIn));

    if (windowObject->m_debugModeOn) {
        windowObject->m_firstMouse = true;
        return;
    }

    if (windowObject->m_camera) {
        float xpos = static_cast<float>(xposIn);
        float ypos = static_cast<float>(yposIn);

        if (windowObject->m_firstMouse) // initially set to true
        {
            windowObject->m_lastX = xpos;
            windowObject->m_lastY = ypos;
            windowObject->m_firstMouse = false;
        }

        float xoffset = xpos - (float)windowObject->m_lastX;
        float yoffset = (float)windowObject->m_lastY - ypos; // reversed since y-coordinates range from bottom to top
        windowObject->m_lastX = xpos;
        windowObject->m_lastY = ypos;

        windowObject->m_camera->ProcessMouseMovement(xoffset, yoffset);
    }
}

bool Window::shouldExit()
{
    return glfwWindowShouldClose(m_window);
}

void Window::swapBuffers()
{
    glfwSwapBuffers(m_window);
}

void Window::scrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
    Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

    if (theWindow->m_camera) {
        theWindow->m_camera->ProcessMouseScroll(static_cast<float>(yoffset));
    }
}

void Window::framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

    theWindow->m_windowSettings.width = width;
    theWindow->m_windowSettings.height = height;

    theWindow->m_camera->setWindowSize(width, height);

    glViewport(0, 0, width, height);
}

GLFWwindow* Window::get()
{
    return m_window;
}

void Window::debugMode()
{
    m_debugModeOn = !m_debugModeOn;

    if (m_debugModeOn) {
        glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
    else {
        glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }
}

bool Window::getWireframeMode()
{
    return m_wireframeModeOn;
}

void Window::setWireframeMode(bool state)
{
    m_wireframeModeOn = state;

    if (m_wireframeModeOn) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    else {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
}

const glm::vec2& Window::getCursorPosition()
{
    glm::vec2 pos = glm::vec2(m_mousePosX, m_mousePosY);

    return pos;
}

} // namespace ENGINE