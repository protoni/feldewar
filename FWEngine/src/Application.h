#ifndef APPLICATION_H
#define APPLICATION_H

#include "Error.h"
#include <dependencies/entt/entt.hpp>


namespace ENGINE
{

class Application
{
public:
    Application();
    ~Application();

    bool Run();
private:
    entt::registry registry;
};
} // namespace ENGINE

#endif // APPLICATION_H