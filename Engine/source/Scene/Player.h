#pragma once
#include "Core/Math.h"
#include "Graphics/Animation.h"
#include "Scene/Level.h"

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>

namespace Engine
{
    enum PlayerAnims
    {
        PLAYER_IDLE = 0,
        PLAYER_RUN,
        PLAYER_ANIM_COUNT = 2,
    };

    class Player
    {
    public:
        Player();

        inline sf::Vector2f& GetPosition() { return m_transform.position; }
        inline void SetPosition(float x, float y) { m_transform.position = sf::Vector2f(x, y); }
        inline void SetLevelHandle(Level* level) { m_levelHandle = level; }

        void Update();
        void Draw();

    private:
        void Jump();
        void HandleAnimation(s8 direction);
        void HandleMovement(s8 direction);
        void HandleCollisions(float xVel, float yVel);

    private:
        float m_moveSpeed;
        bool m_isGrounded;
        Transform m_transform;
        CollisionBox m_collisionBox;
        sf::Vector2f m_velocity;

        sf::Sprite m_sprite;
        Animation m_animations[PLAYER_ANIM_COUNT];
        AnimationController m_animController;

        Level* m_levelHandle;
    };
}
