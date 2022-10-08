#include "Terrain.h"

#include <iostream>

namespace ENGINE
{

Terrain::Terrain(const int gridX, const int gridZ, const char* texture, const char* heightmap)
    : m_x(gridX* SIZE), m_z(gridZ* SIZE)
{
    // Load terrain texture
    m_terrainTexture = new Texture(texture, true);

    // Load terrain height map
    m_terrainHeightMap = new Texture(heightmap, true);

    // Generate terrain
    if (!generateTerrain()) {
        std::cout << "Failed to generate terrain!" << std::endl;
    }

    std::cout << "Generated terrain!" << std::endl;
}

Terrain::~Terrain()
{
    // Destroy VAO
    //glDeleteVertexArrays(1, &m_buf.VAO);

    // Destroy VBOs
    //for (int i = 0; i < m_VBOs.size(); i++) {
    //    glDeleteBuffers(1, &m_VBOs.at(i));
    //}

    if (m_terrainTexture) {
        delete m_terrainTexture;
        m_terrainTexture = NULL;
    }

    if (m_terrainHeightMap) {
        delete m_terrainHeightMap;
        m_terrainHeightMap = NULL;
    }
}

void Terrain::UseTexture() const
{
    m_terrainTexture->use(0);
}

bool Terrain::generateTerrain()
{
    int count = VERTEX_COUNT * VERTEX_COUNT;

    for (int i = 0; i < VERTEX_COUNT; i++) {
        for (int j = 0; j < VERTEX_COUNT; j++) {

            // Calculate terrain position
            unsigned int x = (float)j / ((float)VERTEX_COUNT - 1) * SIZE;
            unsigned int z = (float)i / ((float)VERTEX_COUNT - 1) * SIZE;
            float y = getVertexYpos(j, i);
            m_vertices.push_back(x);
            m_vertices.push_back(y);
            m_vertices.push_back(z);

            // Calculate terrain normals
            glm::vec3 normal = getNormal(j, i);
            m_normals.push_back(normal.x);
            m_normals.push_back(normal.y);
            m_normals.push_back(normal.z);

            // Calculate terrain texture coordinates
            m_texCoords.push_back((float)j / ((float)VERTEX_COUNT - 1));
            m_texCoords.push_back((float)i / ((float)VERTEX_COUNT - 1));
        }
    }

    for (int gz = 0; gz < VERTEX_COUNT - 1; gz++) {
        for (int gx = 0; gx < VERTEX_COUNT - 1; gx++) {
            int topLeft = (gz * VERTEX_COUNT) + gx;
            int topRight = topLeft + 1;
            int bottomLeft = ((gz + 1) * VERTEX_COUNT) + gx;
            int bottomRight = bottomLeft + 1;
            m_indices.push_back(topLeft);
            m_indices.push_back(bottomLeft);
            m_indices.push_back(topRight);
            m_indices.push_back(topRight);
            m_indices.push_back(bottomLeft);
            m_indices.push_back(bottomRight);
        }
    }

    if (!Renderer::LoadData(m_vertices, m_texCoords, m_normals, m_indices, m_buf)) {
        std::cout << "Failed to load terrain!" << std::endl;
        return false;
    }

    m_buf.VertexCount = m_vertices.size();
    m_buf.VertexCountTexture = m_texCoords.size();
    m_buf.VertexCountNormal = m_normals.size();
    m_buf.IndexCount = m_indices.size();

    return true;
}

float Terrain::getVertexYpos(int x, int z)
{
    if (x < 0 || x >= m_terrainHeightMap->getWidth() || z < 0 || z >= m_terrainHeightMap->getHeight())
        return 0.0f;

    float height = m_terrainHeightMap->getRGB(x, z);

    height += MAX_PIXEL_COLOR / 2.0f;
    height /= MAX_PIXEL_COLOR / 2.0f;
    height *= MAX_HEIGHT;
    height -= 20;

    return height;
}

glm::vec3& Terrain::getNormal(int x, int z)
{
    // Get neighboring vertex y values
    float heightL = getVertexYpos(x - 1, z);
    float heightR = getVertexYpos(x + 1, z);
    float heightD = getVertexYpos(x, z - 1);
    float heightU = getVertexYpos(x, z + 1);

    glm::vec3 normal = glm::normalize(glm::vec3(heightL - heightR, 2.0f, heightD - heightU));

    return normal;
}

} // namespace ENGINe