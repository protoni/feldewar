#ifndef PLAYER_H
#define PLAYER_H

#include "FWEngine.h"

namespace ENGINE
{

static const float DEFAULT_RUN_SPEED  = 10.0f;
static const float DEFAULT_TURN_SPEED = 160.0f;

class Player
{

public:
    Player() = default;
    Player(Entity entity, Application& app);
    ~Player();

    // Moving
    const bool MoveForward(const float amount);
    const bool MoveBackward(const float amount);
    const bool Rotate(const float amount);

    void Update();

private:
    // Main application
    Application& m_app;

    Entity m_entity;

    // Speed variables
    float m_currentRunSpeed = 0;
    float m_currentTurnSpeed = 0;

};

} // namespace ENGINE

#endif // PLAYER_H