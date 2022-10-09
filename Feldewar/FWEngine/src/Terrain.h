#ifndef TERRAIN_H
#define TERRAIN_H

#include "DataObjects/Texture.h"
#include "Renderer/Renderer.h"

#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


namespace ENGINE
{

class Terrain
{
public:
    float SIZE = 200.0f;
    float MAX_HEIGHT = 10.0f;
    float MAX_PIXEL_COLOR = 256 * 256 * 256;
    int VERTEX_COUNT = 128;

    //Terrain(const int gridX, const int gridZ, const char* texture, const char* heightmap);
    Terrain(const int gridX, const int gridZ, const Texture& texture, const Texture& heightmap);
    ~Terrain();

    // Get coordinates
    float getX() { return m_x; }
    float getZ() { return m_z; }

    // Get indice count
    int getIndiceCount() { return m_indices.size(); }

    // Calculate normals
    glm::vec3& getNormal(int x, int z);

    // Get buffer data
    const BufferObjectSeparated& GetBuffer() const { return m_buf; }

    // Use current texture
    void UseTexture() const;

    const unsigned int GetVertexCount() const { return m_vertices.size(); }
    const unsigned int GetIndexCount() const { return m_indices.size(); }

private:

    // Generate terrain data
    bool generateTerrain();

    // Read heightmap pixel value and get the height
    float getVertexYpos(int x, int z);

    // Terrain data
    std::vector<float> m_vertices;
    std::vector<float> m_normals;
    std::vector<float> m_texCoords;
    std::vector<unsigned int> m_indices;

    // Buffer objects
    std::vector<unsigned int> m_VBOs;
    unsigned int m_VAO;

    float m_x;
    float m_z;

    // Buffer data
    BufferObjectSeparated m_buf;

    Texture m_terrainTexture;
    Texture m_terrainHeightMap;
};

} // namespace ENGINE

#endif // TERRAIN_H