#include "Mesh.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

#include "DebugMacros.h"

//#include <btBulletDynamicsCommon.h>


Mesh::Mesh(
    Shader& shader,
    std::vector<float>& vertices,
    std::vector<unsigned int>& indices
) :
    m_shader(shader), m_vertices(vertices), m_indices(indices)
{
    create();
}


Mesh::~Mesh()
{
}


void Mesh::create()
{

}

