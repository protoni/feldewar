#ifndef RENDERER_OPENGL_H
#define RENDERER_OPENGL_H

#include <vector>

#include <glm/glm.hpp>

namespace ENGINE
{

    class RendererOpenGL
    {
    public:
        RendererOpenGL();
        ~RendererOpenGL();

        bool Init();

        // Load vertex data
        void loadVertices(std::vector<float>& data, unsigned int vbo) const;

        // Load index data
        void loadIndices(std::vector<unsigned int>& data, unsigned int vbo) const;

        // Define an array of generic vertex attribute data
        void SetVertexAttribPointer(
            unsigned int attrNmbr,
            unsigned int coordSize,
            unsigned int stride
        );

        // Load square vertices and indices to GPU
        void LoadSquare();

        // Create Vertex buffer object and return the ID
        unsigned int CreateVertexBuffer();

        // Create Vertex array object and return the ID
        unsigned int CreateVertexArray();

        // Bind vertex buffer
        void BindVertexBuffer(unsigned int buffer);

        // Bind vertex array
        void BindVertexArray(unsigned int array);

        // Un bind vertex array
        void UnBindVertexArray();

        // Draw primitive square
        void DrawSquare();

        // Clear screen
        void ClearScreen(glm::vec4 color, int settings) const;

        // Draw rectangle
        void DrawRect(const glm::mat4& transform, const glm::vec3& position);

    private:
        std::vector<unsigned int> m_VBOs;
        std::vector<unsigned int> m_VAOs;

        // Primitives
        unsigned int m_squareVAO;
    };

}

#endif // RENDERER_OPENGL_H
