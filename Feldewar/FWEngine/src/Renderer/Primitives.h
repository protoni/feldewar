#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#include "Mesh.h"
#include "Shapes.h"

namespace ENGINE
{
namespace PRIMITIVES
{

    // 2D rectangle primitive
    class Rectangle2D : public Mesh
    {

    public:
        Rectangle2D()
            : Mesh(rectangle_vertices, rectangle_indices) {}
        ~Rectangle2D() {}
    };

    // 3D cube primitive
    class Cube3D : public Mesh
    {

    public:
        Cube3D()
            : Mesh(cube_vertices, cube_indices) {}
        ~Cube3D() {}
    };


} // namespace PRIMITIVES
} // namespace ENGINE

#endif // PRIMITIVES_H
