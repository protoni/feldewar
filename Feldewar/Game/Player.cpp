#include "Player.h"

namespace ENGINE
{
    Player::Player(Entity entity) : m_entity(entity)
    {
    }

    Player::~Player()
    {
    }

    const bool Player::MoveForward(const float amount)
    {
        return m_entity.MoveForward(amount);
    }

    const bool Player::Rotate(const float amount)
    {
        return m_entity.RotateHorizontal(amount);
    }

    const bool Player::Update()
    {

    }

} // namespace ENGINE
