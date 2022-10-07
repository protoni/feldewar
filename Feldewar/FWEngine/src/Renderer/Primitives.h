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


} // namespace PRIMITIVES
} // namespace ENGINE

#endif // PRIMITIVES_H
