#ifndef SETTINGS_H
#define SETTINGS_H

#include <string>

namespace ENGINE
{
//struct DataSettings;
//struct TerrainSettings;
//struct WindowSettings;



struct WindowSettings
{
    std::string name    = "Unknown";
    unsigned int width  = 1600;
    unsigned int height = 800;
};

struct DataSettings
{
    std::string modelPath   = "./";
    std::string texturePath = "./";
};

struct TerrainSettings
{
    std::string heightMap = "heightmap.png";
    float size = 800.0f;
};

struct Settings
{
    DataSettings data;
    TerrainSettings terrain;
    WindowSettings window;
};

} // namespace ENGINE
#endif // SETTINGS_H