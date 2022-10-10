#ifndef MESH_H
#define MESH_H

#include "Renderer.h"

#include <vector>

namespace ENGINE
{

class Mesh
{

public:
    Mesh() = default;
    Mesh(
        const std::vector<float>& vertices,
        const std::vector<unsigned int>& indices
    );

    ~Mesh();

    const BufferObject& GetBuffer() const { return m_buf; }

private:
    std::vector<float> m_vertices;
    std::vector<unsigned int> m_indices;

    // Create mesh
    void create();

    // Buffer data
    BufferObject m_buf;

    // Buffer objects
    unsigned int m_VBO;
    unsigned int m_EBO;

    // Array objects
    unsigned int m_VAO;
};

} // namespace ENGINE

#endif // MESH_H