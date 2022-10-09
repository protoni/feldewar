#ifndef TEXTURE_H
#define TEXTURE_H

#include "stb_image.h"

namespace ENGINE
{

class Texture
{

public:
    // If initialization is successful, set to true
    bool Loaded = false;

    Texture() = default;
    Texture(const char* path, bool useRGBA = false);
    ~Texture();

    bool load();

    virtual void Use(int offset) const;

    unsigned int getTexture();

    /* Deactivate texture */
    static void deactivate();

    // Get image data
    unsigned char* getData() { return m_data; }

    // Get image properties
    const int GetWidth() const { return m_width; }
    const int GetHeight() const { return m_height; }
    int getNrChannels() { return m_nrChannels; }

    // Get image's RGB value
    //float getRGB(int x, int y);
    const float GetRGB(const unsigned int x, const unsigned int y) const;

    // Clear image data
    void Clear() const;

private:
    /* Path of the texture file */
    const char* m_path;

    /* Does the texture image use RGBA channel */
    bool m_useRGBA;

    unsigned int m_texture;

    // Store image data here
    stbi_uc* m_data;

    // Store image properties here
    int m_width = 0;
    int m_height = 0;
    int m_nrChannels = 0;
};

} // namespace ENGINE

#endif // TEXTURE_H