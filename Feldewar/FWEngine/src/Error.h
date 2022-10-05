#ifndef ERROR_H
#define ERROR_H

#include <string>
#include <iostream>

namespace ENGINE
{

static const std::string ERR_UNKNOWN           = "Unknown error";
static const std::string ERR_WINDOW_CREATION   = "Window creation failed";
static const std::string ERR_CAMERA_CREATION   = "Camera creation failed";
static const std::string ERR_INPUT_CREATION    = "Input creation failed";
static const std::string ERR_RENDERER_CREATION = "Renderer creation failed";
static const std::string ERR_SCENE_CREATION    = "Scene creation failed! Renderer not initialized!";

enum class ErrorMessage
{
    UnkownError = -1,
    NoError     =  0,
    WindowCreationError,
    CameraCreationError,
    InputCreationError,
    RendererCreationError,
    SceneCreationError
};

struct Error
{
    ErrorMessage msg;

    inline void Set(ErrorMessage message) { msg = message; }
    inline const ErrorMessage Get() const { return msg; }
    inline const bool IsErr() const { return (bool)msg; }

    inline const std::string& GetMsg() const
    {
        switch (msg)
        {
        case ErrorMessage::UnkownError:
            return ERR_UNKNOWN;
            break;

        case ErrorMessage::WindowCreationError:
            return ERR_WINDOW_CREATION;
            break;

        case ErrorMessage::CameraCreationError:
            return ERR_CAMERA_CREATION;
            break;

        case ErrorMessage::InputCreationError:
            return ERR_INPUT_CREATION;
            break;

        case ErrorMessage::RendererCreationError:
            return ERR_RENDERER_CREATION;
            break;

        case ErrorMessage::SceneCreationError:
            return ERR_SCENE_CREATION;
            break;
        }

        return ERR_UNKNOWN;
    }

    inline void Print() const
    {
        std::cout << "Error: " << GetMsg() << std::endl;
    }
};
} // namespace ENGINE
#endif // ERROR_H
