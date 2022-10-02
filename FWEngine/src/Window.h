#ifndef WINDOW_H
#define WINDOW_H

#include "Settings.h"
#include "Camera.h"

#include <string>
#include <memory>

#include <dependencies/glad/glad.h>
#include <dependencies/glm/glm.hpp>
#include <dependencies/GLFW/glfw3.h>

namespace ENGINE
{

class Window
{
public:
    Window(WindowSettings& settings, std::shared_ptr<Camera> camera);
    ~Window();

    bool init();

    GLFWwindow* get();
    bool shouldExit();
    void swapBuffers();
    void debugMode();
    void wireframeMode();
    bool getWireframeMode();
    void setWireframeMode(bool state);

    // Get cursor position
    const glm::vec2& getCursorPosition();

    // Get window size
    const glm::vec2& getSize()
    {
        glm::vec2 size = glm::vec2(m_windowSettings.width, m_windowSettings.height);
        return size;
    }

    // Shutdown GLFW
    void Cleanup() { glfwTerminate(); }

private:
    // Callback functions
    static void mouseCallback(GLFWwindow* window, double xposIn, double yposIn);
    static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
    static void framebufferSizeCallback(GLFWwindow* window, int width, int height);

    // Objects
    std::shared_ptr<Camera> m_camera = nullptr;
    GLFWwindow* m_window = nullptr;

    // Settings
    WindowSettings& m_windowSettings;
    bool m_debugModeOn;
    bool m_wireframeModeOn;

    // Mouse
    bool m_firstMouse;
    double m_lastX;
    double m_lastY;

    // Mouse screen position
    float m_mousePosX;
    float m_mousePosY;
};

} // namespace ENGINE

#endif // WINDOW_H