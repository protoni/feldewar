#ifndef RENDERER_OPENGL_H
#define RENDERER_OPENGL_H

#include <vector>

#include <glm/glm.hpp>

namespace ENGINE
{

struct BufferObject
{
    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;

    unsigned int VerticeCount;
    unsigned int IndiceCount;

    BufferObject()
        : VAO(0)
        , VBO(0)
        , EBO(0)
        , VerticeCount(0)
        , IndiceCount(0)
    {}
};

class RendererOpenGL
{
public:
    RendererOpenGL();
    ~RendererOpenGL();

    bool Init();

    // Load vertex data
    static void LoadVertices(const std::vector<float>& data, const unsigned int vbo);

    // Load index data
    static void LoadIndices(const std::vector<unsigned int>& data, const unsigned int vbo);

    // Define an array of generic vertex attribute data
    static void SetVertexAttribPointer(
        const unsigned int attrNmbr,
        const unsigned int size,
        const unsigned int coordSize,
        const unsigned int stride
    );

    // Load square vertices and indices to GPU
    void LoadSquare();

    // Create Vertex buffer object and return the ID
    static unsigned int CreateVertexBuffer();

    // Create Vertex array object and return the ID
    static unsigned int CreateVertexArray();

    // Bind vertex buffer
    static void BindVertexBuffer(const unsigned int buffer);

    // Bind vertex array
    static void BindVertexArray(const unsigned int array);

    // Un bind vertex array
    static void UnBindVertexArray();

    // Unbind vertex and element array buffers
    static void UnBindBuffer();

    // Draw primitive square
    void DrawSquare(const BufferObject& buf) const;

    // Clear screen
    void ClearScreen(glm::vec4 color, int settings) const;

    // Draw rectangle
    void DrawRect(const glm::mat4& transform, const glm::vec3& position);

    // Load vertex data to the GPU
    static void LoadData(
        const std::vector<float>& vertices,
        const std::vector<unsigned int>& indices,
        BufferObject& buf
    );

private:
    std::vector<unsigned int> m_VBOs;
    std::vector<unsigned int> m_VAOs;

    // Primitives
    unsigned int m_squareVAO;
    unsigned int m_squareEBO;
};

}

#endif // RENDERER_OPENGL_H
