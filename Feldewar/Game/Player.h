#ifndef PLAYER_H
#define PLAYER_H

#include "FWEngine.h"

namespace ENGINE
{

class Player
{

public:
    Player() = default;
    Player(Entity entity);
    ~Player();

    const bool MoveForward(const float amount);

    const bool Rotate(const float amount);

    const bool Update();

private:
    Entity m_entity;

};

} // namespace ENGINE

#endif // PLAYER_H