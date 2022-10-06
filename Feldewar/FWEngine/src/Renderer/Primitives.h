#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#include "Mesh.h"
#include "Shapes.h"
#include "Shader.h"

namespace ENGINE
{

class Rectangle : public Mesh
{

public:
    BufferObject BufferData;

    Rectangle() : Mesh(square_vertices, square_indices, BufferData) {}
    ~Rectangle() {}

    //const BufferObject& GetBuffer() const { return BufferData; }
};

}

#endif // PRIMITIVES_H
