#ifndef ENGINE_UTILS_H
#define ENGINE_UTILS_H

#include <iostream>
#include <string>
#include <chrono>
#include <cstdint>

#include <glm/glm.hpp>


namespace ENGINE
{
namespace UTILS
{

    // Debug prints
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

    static void PrintVec(const float x, const float y, const std::string& name = std::string("Vec2"))
    {
        std::cout << name << ": [ " << x << ", " << y << " ]" << std::endl;
    }

    static void PrintVec(const float x, const float y, const float z, const std::string& name = std::string("Vec3"))
    {
        std::cout << name << ": [ " << x << ", " << y << ", " << z << " ]" << std::endl;
    }

    static void PrintVec(const float x, const float y, const float z, const float w, const std::string& name = std::string("Vec4"))
    {
        std::cout << name << ": [ " << x << ", " << y << ", " << z << ", " << w << " ]" << std::endl;
    }

    // Time
    static const uint64_t GetTimestampMs()
    {
        using namespace std::chrono;
        return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    }

} // namespace UTILS
} // namespace ENGINE

#endif // ENGINE_UTILS_H