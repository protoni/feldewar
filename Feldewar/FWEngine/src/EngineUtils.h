#ifndef ENGINE_UTILS_H
#define ENGINE_UTILS_H

#include <iostream>
#include <string>

#include <glm/glm.hpp>

namespace ENGINE
{
namespace UTILS
{

    static void PrintVec(const glm::vec2& vector, const std::string& name = std::string("Vec2"))
    {
        std::cout << name << ": [ " << vector.x << ", " << vector.y << " ]" << std::endl;
    }

    static void PrintVec(const glm::vec3& vector, const std::string& name = std::string("Vec3"))
    {
        std::cout << name << ": [ " << vector.x << ", " << vector.y << ", " << vector.z << " ]" << std::endl;
    }

    static void PrintVec(const glm::vec4& vector, const std::string& name = std::string("Vec4"))
    {
        std::cout << name << ": [ " << vector.x << ", " << vector.y << ", " << vector.z << ", " << vector.w << " ]" << std::endl;
    }

} // namespace UTILS
} // namespace ENGINE

#endif // ENGINE_UTILS_H