#ifndef ERROR_H
#define ERROR_H

#include <string>
#include <iostream>

namespace ENGINE
{

static const std::string ERR_UNKNOWN =         "Unknown error";
static const std::string ERR_WINDOW_CREATION = "Window creation failed";

enum class ErrorMessage
{
    UnkownError = -1,
    NoError     =  0,
    WindowCreationError
};

struct Error
{
    ErrorMessage msg;

    inline const ErrorMessage Get() const { return msg; }
    inline const bool IsErr() const { return (bool)msg; }

    inline const std::string& GetMsg() const
    {
        switch (msg)
        {
        case ErrorMessage::UnkownError:
            return ERR_UNKNOWN;

        case ErrorMessage::WindowCreationError:
            return ERR_WINDOW_CREATION;


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
