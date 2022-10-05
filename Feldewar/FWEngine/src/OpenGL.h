#ifndef OPENGL_H
#define OPENGL_H

#include <vector>

namespace
{

class OpenGL
{
public:
    OpenGL();
    ~OpenGL();

    static bool Init();

    // Load vertex data
    bool loadVertices(
        float* data,
        unsigned int size,
        int attrNmbr,
        int coordSize,
        int stride
    ) const;

    // Load index data
    bool loadIndices(float* data, unsigned int size) const;

private:
    std::vector<unsigned int> m_VBOs;
};

}

#endif // OPENGL_H
