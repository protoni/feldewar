#ifndef SHAPES_H
#define SHAPES_H

#include <vector>

namespace ENGINE
{

static const std::vector<float> square_vertices = {
    // Location             // Texture coords    // Normals
    -0.5f,  0.5f, 0.0f,     0.0f, 0.0f,          0.0f, 1.0f, 0.0f,  // far left
     0.5f,  0.5f, 0.0f,     0.0f, 0.0f,          0.0f, 1.0f, 0.0f,  // far rigt
     0.5f, -0.5f, 0.0f,     0.0f, 0.0f,          0.0f, 1.0f, 0.0f,  // near right
    -0.5f, -0.5f, 0.0f,     0.0f, 0.0f,          0.0f, 1.0f, 0.0f   // near left
};

static const std::vector<unsigned int> square_indices = {
    0, 1, 2,
    2, 3, 0
};

}

#endif // SHAPES_H