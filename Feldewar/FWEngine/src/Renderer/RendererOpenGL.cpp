#include "RendererOpenGL.h"
#include "Shapes.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace ENGINE
{

    RendererOpenGL::RendererOpenGL()
    {
    }

    RendererOpenGL::~RendererOpenGL()
    {
    }

    void RendererOpenGL::LoadSquare()
    {
        std::vector<float> vertices = square_vertices;
        std::vector<unsigned int> indices = square_indices;

        m_squareVAO = CreateVertexArray();
        BindVertexArray(m_squareVAO);

        loadVertices(vertices, CreateVertexBuffer());
        loadIndices(indices, CreateVertexBuffer());

        SetVertexAttribPointer(0, 8, 0);
        SetVertexAttribPointer(1, 8, 3);
        SetVertexAttribPointer(2, 8, 5);

        UnBindVertexArray();
    }

    void RendererOpenGL::DrawSquare()
    {
        BindVertexArray(m_squareVAO);
        glDrawElements(GL_TRIANGLES, square_indices.size(), GL_UNSIGNED_INT, 0);
    }

    void RendererOpenGL::ClearScreen(glm::vec4 color, int settings) const
    {
        glClearColor(color.x, color.y, color.z, color.w);
        glClear(settings);
    }

    void RendererOpenGL::DrawRect(const glm::mat4& transform, const glm::vec3& position)
    {
    }

    bool RendererOpenGL::Init()
    {
        // Load primitive data
        LoadSquare();

        return true;
    }

    unsigned int RendererOpenGL::CreateVertexBuffer()
    {
        unsigned int VBO;
        glGenBuffers(1, &VBO);
        m_VBOs.push_back(VBO);

        return VBO;
    }

    unsigned int RendererOpenGL::CreateVertexArray()
    {
        unsigned int VAO;
        glGenVertexArrays(1, &VAO);
        m_VAOs.push_back(VAO);

        return VAO;
    }

    void RendererOpenGL::BindVertexBuffer(unsigned int buffer)
    {
        glBindBuffer(GL_ARRAY_BUFFER, buffer);
    }

    void RendererOpenGL::BindVertexArray(unsigned int array)
    {
        glBindVertexArray(array);
    }

    void RendererOpenGL::UnBindVertexArray()
    {
        glBindVertexArray(0);
    }

    void RendererOpenGL::SetVertexAttribPointer(
        unsigned int attrNmbr,
        unsigned int coordSize,
        unsigned int stride
    )
    {
        glVertexAttribPointer(attrNmbr, coordSize, GL_FLOAT, GL_FALSE, coordSize * sizeof(float), (void*)(stride * sizeof(float)));
        glEnableVertexAttribArray(attrNmbr);
    }

    void RendererOpenGL::loadVertices(std::vector<float>& data, unsigned int vbo) const
    {
        // Load data to GPU
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(data.at(0)) * data.size(), &data.at(0), GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void RendererOpenGL::loadIndices(std::vector<unsigned int>& data, unsigned int vbo) const
    {

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.size() * sizeof(data.at(0)), &data[0], GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }


}