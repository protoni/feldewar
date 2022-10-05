#ifndef MESH_H
#define MESH_H

#include "Shader.h"
#include "Renderer.h"
#include <vector>

class Mesh
{

public:
    Mesh(
        //std::
        Shader& shader,
        std::vector<float>& vertices,
        std::vector<unsigned int>& indices
    );

    ~Mesh();

private:
    Shader m_shader;
    std::vector<float> m_vertices;
    std::vector<unsigned int> m_indices;

    // Create mesh
    void create();

    // Buffer objects
    unsigned int m_VBO;
    unsigned int m_EBO;

    // Array objects
    unsigned int m_VAO;
};

#endif // MESH_H