#include "Player.h"
#include "EngineUtils.h"


namespace ENGINE
{
    Player::Player(Entity entity, Application& app)
        : m_entity(entity), m_app(app)
    {
    }

    Player::~Player()
    {
    }

    const bool Player::MoveForward(const float amount)
    {
        return m_entity.MoveForward(amount);
    }

    const bool Player::MoveBackward(const float amount)
    {
        return m_entity.MoveBackward(amount);
    }

    const bool Player::Rotate(const float amount)
    {
        return m_entity.RotateHorizontal(amount);
    }

    void Player::Update()
    {
        if (!m_app.GetFreeLookOn()) {
            if (m_app.KeyPressed(INPUT_EVENTS::INPUT_EVENT_W)) {
                std::cout << "W pressed" << std::endl;
                //MoveForward(DEFAULT_RUN_SPEED);
                m_currentRunSpeed = DEFAULT_RUN_SPEED;
            }

            else if (m_app.KeyPressed(INPUT_EVENTS::INPUT_EVENT_S)) {
                std::cout << "S pressed" << std::endl;
                //MoveBackward(DEFAULT_RUN_SPEED);
                m_currentRunSpeed = -DEFAULT_RUN_SPEED;
            }
            else
                m_currentRunSpeed = 0;


            if (m_app.KeyPressed(INPUT_EVENTS::INPUT_EVENT_A)) {
                std::cout << "A pressed" << std::endl;
                //Rotate(-DEFAULT_TURN_SPEED);
                m_currentTurnSpeed = DEFAULT_TURN_SPEED;
            }

            else if (m_app.KeyPressed(INPUT_EVENTS::INPUT_EVENT_D)) {
                std::cout << "D pressed" << std::endl;
                //Rotate(DEFAULT_TURN_SPEED);
                m_currentTurnSpeed = -DEFAULT_TURN_SPEED;
            }
            else
                m_currentTurnSpeed = 0;

            if (!Rotate(m_currentTurnSpeed * m_app.GetDeltaTime()))
                std::cout << "Failed to rotate!" << std::endl;

            std::cout << "m_entity.GetRotationY(): " << m_entity.GetRotationY() << std::endl;
            float distance = m_currentRunSpeed * m_app.GetDeltaTime();
            float dx = distance * glm::sin(glm::radians(m_entity.GetRotationY()));
            float dz = distance * glm::cos(glm::radians(m_entity.GetRotationY()));
            m_entity.Move(dx, 0, dz);
            UTILS::PrintVec(dx, 0, dz, "Move vector");
        }
    }

} // namespace ENGINE
