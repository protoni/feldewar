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
        //std::vector<float> vertices = square_vertices;
        //std::vector<unsigned int> indices = square_indices;
        //
        //m_squareVAO = CreateVertexArray();
        //BindVertexArray(m_squareVAO);
        //
        //loadVertices(vertices, CreateVertexBuffer());
        //
        //m_squareEBO = CreateVertexBuffer();
        //loadIndices(indices, m_squareEBO);
        //
        //SetVertexAttribPointer(0, 3, 8, 0);
        //SetVertexAttribPointer(1, 2, 8, 3);
        //SetVertexAttribPointer(2, 3, 8, 5);
        //
        //UnBindVertexArray();
        //UnBindBuffer();
    }

    void RendererOpenGL::DrawSquare(const BufferObject& buf) const
    {
        BindVertexArray(buf.VAO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buf.EBO);
        glDrawElements(GL_TRIANGLES, buf.IndiceCount, GL_UNSIGNED_INT, 0);
    }

    void RendererOpenGL::ClearScreen(glm::vec4 color, int settings) const
    {
        glClearColor(color.x, color.y, color.z, color.w);
        glClear(settings);
    }

    void RendererOpenGL::DrawRect(const glm::mat4& transform, const glm::vec3& position)
    {
    }

    void RendererOpenGL::DrawTerrain(const BufferObjectSeparated& buf) const
    {
        BindVertexArray(buf.VAO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buf.VBOIndex);
        glDrawElements(GL_TRIANGLES, buf.IndexCount, GL_UNSIGNED_INT, 0);
    }

    void RendererOpenGL::LoadData(
        const std::vector<float>& vertices,
        const std::vector<unsigned int>& indices,
        BufferObject& buf
    )
    {
        // Create buffers
        buf.VAO = CreateVertexArray();
        buf.VBO = CreateVertexBuffer();
        buf.EBO = CreateVertexBuffer();

        // Bind vertex array
        BindVertexArray(buf.VAO);

        // Load vertex data
        LoadVertices(vertices, buf.VBO);

        // Load index data
        LoadIndices(indices, buf.EBO);

        // Setup VAO
        SetVertexAttribPointer(0, 3, 8, 0);
        SetVertexAttribPointer(1, 2, 8, 3);
        SetVertexAttribPointer(2, 3, 8, 5);
        
        // Unbind buffers
        UnBindVertexArray();
        UnBindBuffer();
    }

    void RendererOpenGL::LoadData(
        const std::vector<float>& vertices,
        const std::vector<float>& textureCoords,
        const std::vector<float>& normals,
        const std::vector<unsigned int>& indices,
        BufferObjectSeparated& buf)
    {
        // Create buffers
        buf.VAO = CreateVertexArray();
        buf.VBOVertex = CreateVertexBuffer();
        buf.VBOTexture = CreateVertexBuffer();
        buf.VBONormal = CreateVertexBuffer();
        buf.VBOIndex = CreateVertexBuffer();

        // Bind vertex array
        BindVertexArray(buf.VAO);

        // Load index data
        LoadIndices(indices, buf.VBOIndex);

        // Load vertex, texture coordinate and normal data + setup VAOs
        LoadVertices(vertices, buf.VBOVertex);
        SetVertexAttribPointer(0, 3, 3, 0);

        LoadVertices(textureCoords, buf.VBOTexture);
        SetVertexAttribPointer(1, 2, 2, 3);

        LoadVertices(normals, buf.VBONormal);
        SetVertexAttribPointer(2, 3, 3, 5);
        
        // Unbind buffers
        UnBindVertexArray();
        UnBindBuffer();
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
        //m_VBOs.push_back(VBO);

        return VBO;
    }

    unsigned int RendererOpenGL::CreateVertexArray()
    {
        unsigned int VAO;
        glGenVertexArrays(1, &VAO);
        //m_VAOs.push_back(VAO);

        return VAO;
    }

    void RendererOpenGL::BindVertexBuffer(unsigned int buffer)
    {
        glBindBuffer(GL_ARRAY_BUFFER, buffer);
    }

    void RendererOpenGL::BindVertexArray(const unsigned int array)
    {
        glBindVertexArray(array);
    }

    void RendererOpenGL::UnBindVertexArray()
    {
        glBindVertexArray(0);
    }

    void RendererOpenGL::UnBindBuffer()
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    void RendererOpenGL::SetVertexAttribPointer(
        unsigned int attrNmbr,
        unsigned int size,
        unsigned int coordSize,
        unsigned int stride
    )
    {
        glVertexAttribPointer(attrNmbr, size, GL_FLOAT, GL_FALSE, coordSize * sizeof(float), (void*)(stride * sizeof(float)));
        glEnableVertexAttribArray(attrNmbr);
    }

    void RendererOpenGL::LoadVertices(const std::vector<float>& data, const unsigned int vbo)
    {
        // Load data to GPU
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(data.at(0)) * data.size(), &data.front(), GL_STATIC_DRAW);
        //glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void RendererOpenGL::LoadIndices(const std::vector<unsigned int>& data, const unsigned int vbo)
    {

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.size() * sizeof(data.at(0)), &data[0], GL_STATIC_DRAW);
        //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }


}