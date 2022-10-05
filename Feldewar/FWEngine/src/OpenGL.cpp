#include "OpenGL.h"
#include "Shapes.h"

#include "../dependencies/glad/glad.h"
#include "../dependencies/GLFW/glfw3.h"

namespace
{

    OpenGL::OpenGL()
    {
    }

    OpenGL::~OpenGL()
    {
    }

    bool OpenGL::Init()
    {
        return false;
    }

    bool OpenGL::loadVertices(
        float* data,
        unsigned int size,
        int attrNmbr,
        int coordSize,
        int stride
    ) const
    {
        unsigned int VBO;
        glGenBuffers(1, &VBO);

        // Load data to GPU
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * size, &data[0], GL_STATIC_DRAW);

        // Set VAO coordinates
        glVertexAttribPointer(attrNmbr, coordSize, GL_FLOAT, GL_FALSE, coordSize * sizeof(float), (void*)(stride * sizeof(float)));
        glEnableVertexAttribArray(attrNmbr);

        return true;
    }

    bool OpenGL::loadIndices(float* data, unsigned int size) const
    {
        unsigned int VBO;
        glGenBuffers(1, &VBO);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, size * data[0], &data[0], GL_STATIC_DRAW);

        return true;
    }


}