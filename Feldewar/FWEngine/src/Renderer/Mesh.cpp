#include "Mesh.h"
#include "DebugMacros.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>


namespace ENGINE
{

Mesh::Mesh(
    const std::vector<float>& vertices,
    const std::vector<unsigned int>& indices
) :
    m_vertices(vertices), m_indices(indices)
{
    create();
}


Mesh::~Mesh()
{
}


void Mesh::create()
{
    if (!Renderer::LoadData(m_vertices, m_indices, m_buf)) {
        std::cout << "Failed to create mesh!" << std::endl;
    }

    m_buf.VerticeCount = m_vertices.size();
    m_buf.IndiceCount = m_indices.size();
}

} // namespace ENGINE