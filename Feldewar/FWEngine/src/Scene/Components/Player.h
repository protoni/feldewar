#ifndef PLAYER_H
#define PLAYER_H

#include "Renderer/Mesh.h"

namespace ENGINE
{

class Player
{

public:
    Player() = default;
    Player(const Mesh& mesh);
    ~Player();

};

} // namespace ENGINE

#endif // PLAYER_H