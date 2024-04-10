#pragma once
#include "Scene/Level.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>

namespace Engine
{
    class Player
    {
    public:
        Player();

        inline sf::RectangleShape& GetShape() { return m_shape; }

        inline sf::Vector2f& GetPosition() { return m_position; }
        inline void SetPosition(float x, float y) { m_position = sf::Vector2f(x, y); }
        inline void SetLevelHandle(Level* level) { m_levelHandle = level; }

        void Update();
        void Draw();

    private:
        void Jump();
        void HandleMovement(float direction);
        void HandleCollisions(float xVel, float yVel);

    private:
        sf::Vector2f m_position;
        sf::Vector2f m_velocity;

        float m_moveSpeed;
        bool m_isGrounded;
        sf::RectangleShape m_shape;
        Level* m_levelHandle;
    };
}
