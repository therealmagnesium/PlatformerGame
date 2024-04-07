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
        inline void SetLevelHandle(Level* level) { m_levelHandle = level; }

        void Update();
        void Draw();

    private:
        void HandleCollisions(float xVel, float yVel);

    private:
        float m_moveSpeed;
        sf::Vector2f m_velocity;
        sf::RectangleShape m_shape;
        Level* m_levelHandle;
    };
}
