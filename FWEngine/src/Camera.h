#ifndef CAMERA_H
#define CAMERA_H

#include <dependencies/glad/glad.h> // include glad to get all the required OpenGL headers
#include <dependencies/glm/glm.hpp>
#include <dependencies/glm/gtc/matrix_transform.hpp>

#include <vector>

namespace ENGINE
{

// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
enum class CameraMovement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

// Default camera values
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

class Camera
{
public:
    // Camera attributes
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;

    // Euler angles
    float Yaw;
    float Pitch;

    // Camera options
    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;

    // Store current window size here
    void setWindowSize(int width, int height) {
        m_windowWidth = (float)width;
        m_windowHeight = (float)height;
    }

    // Store mouse cursor screen coordinates here
    void setMousePos(float mousePosX, float mousePosY)
    {
        m_mousePosX = mousePosX;
        m_mousePosY = mousePosY;
    }

    glm::vec2& getWindowSize()
    {
        glm::vec2 size = glm::vec2(m_windowWidth, m_windowHeight);
        return size;
    }

    // Get mouse cursor screen coordinates
    glm::vec2& getMousePos()
    {
        glm::vec2 pos = glm::vec2(m_mousePosX, m_mousePosY);
        return pos;
    }

    // Get mouse cursor world coordinates
    glm::vec2& getMouseWorldPos()
    {
        glm::vec2 pos = glm::vec2(m_mousePosX + Position.x, m_mousePosY + Position.y);
        return pos;
    }

    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
        float yaw = YAW, float pitch = PITCH)
        : Front(glm::vec3(0.0f, 0.0f, -1.0f)),
        MovementSpeed(SPEED),
        MouseSensitivity(SENSITIVITY),
        Zoom(ZOOM)
    {
        Position = position;
        WorldUp = up;
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors();
    }

    glm::mat4 GetViewMatrix()
    {
        return glm::lookAt(Position, Position + Front, Up);
    }

    void ProcessKeyboard(CameraMovement direction, double deltaTime)
    {
        float velocity = MovementSpeed * (float)deltaTime;
        if (direction == CameraMovement::FORWARD)
            Position += Front * velocity;
        if (direction == CameraMovement::BACKWARD)
            Position -= Front * velocity;
        if (direction == CameraMovement::LEFT)
            Position -= Right * velocity;
        if (direction == CameraMovement::RIGHT)
            Position += Right * velocity;
        if (direction == CameraMovement::UP)
            Position += Up * velocity;
        if (direction == CameraMovement::DOWN)
            Position -= Up * velocity;

        // Set FPS camera
        //Position.y = 0.0f;
    }

    // processes input received from a mouse input system. Expects the offset value in both the x and y direction.
    void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true)
    {
        xoffset *= MouseSensitivity;
        yoffset *= MouseSensitivity;

        Yaw += xoffset;
        Pitch += yoffset;

        // make sure that when pitch is out of bounds, screen doesn't get flipped
        if (constrainPitch)
        {
            if (Pitch > 89.0f)
                Pitch = 89.0f;
            if (Pitch < -89.0f)
                Pitch = -89.0f;
        }

        // update Front, Right and Up Vectors using the updated Euler angles
        updateCameraVectors();
    }

    // processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
    void ProcessMouseScroll(float yoffset)
    {
        Zoom -= (float)yoffset;
        if (Zoom < 1.0f)
            Zoom = 1.0f;
        if (Zoom > 45.0f)
            Zoom = 45.0f;
    }

private:
    void updateCameraVectors()
    {
        // calculate the new Front vector
        glm::vec3 front;
        front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        front.y = sin(glm::radians(Pitch));
        front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        Front = glm::normalize(front);
        // also re-calculate the Right and Up vector
        Right = glm::normalize(glm::cross(Front, WorldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
        Up = glm::normalize(glm::cross(Right, Front));
    }

    // Mouse screen coordinates
    float m_mousePosX;
    float m_mousePosY;

    // Window size
    float m_windowWidth;
    float m_windowHeight;
};
} // namespace ENGINE

#endif // CAMERA_H