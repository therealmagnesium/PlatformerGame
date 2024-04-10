#include "Scene/Player.h"
#include "Core/Base.h"
#include "Core/Input.h"
#include "Core/Log.h"
#include "Core/Math.h"
#include "Graphics/Renderer.h"
#include "Scene/Level.h"
#include "Scene/Tile.h"

#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <cassert>

namespace Engine
{
    Player::Player()
    {
        m_position = sf::Vector2f(0.f, 0.f);
        m_velocity = sf::Vector2f(0.f, 0.f);

        m_shape.setPosition(0.f, 0.f);
        m_shape.setSize(sf::Vector2f(TILE_SIZE, TILE_SIZE));
        m_shape.setFillColor(sf::Color(14, 68, 82));
        m_shape.setOutlineColor(sf::Color(14, 68, 82));
        m_shape.setOutlineThickness(0.f);

        m_moveSpeed = 700.f;
        m_isGrounded = false;
    }

    void Player::Update()
    {
        float direction = Input::GetAxis("Horizontal");
        this->HandleMovement(direction);
    }

    void Player::HandleMovement(float direction)
    {
        if (Input::IsKeyTyped(sf::Keyboard::Up) && m_isGrounded)
            this->Jump();

        m_velocity.x = m_moveSpeed * direction;
        m_position.x += m_velocity.x * Time::deltaTime;
        this->HandleCollisions(m_velocity.x, 0.f);

        m_velocity.y += GRAVITY * m_moveSpeed * Time::deltaTime;
        m_position.y += m_velocity.y * Time::deltaTime;
        this->HandleCollisions(0.f, m_velocity.y);
    }

    void Player::HandleCollisions(float xVel, float yVel)
    {
        assert(m_levelHandle);

        LevelData& levelData = m_levelHandle->GetData();
        Tile* tiles = levelData.tiles.data();
        u32 numTiles = levelData.tiles.size();
        m_isGrounded = false;

        for (u32 i = 0; i < numTiles; i++)
        {
            Tile& tile = tiles[i];

            if (CheckAABB(sf::FloatRect(m_position, m_shape.getSize()), tile.GetShape().getGlobalBounds()))
            {
                if (xVel < 0)
                {
                    m_velocity.x = 0.f;
                    m_position.x = tile.GetShape().getPosition().x + m_shape.getSize().x;
                }

                if (xVel > 0)
                {
                    m_velocity.x = 0.f;
                    m_position.x = tile.GetShape().getPosition().x - m_shape.getSize().x;
                }

                if (yVel < 0)
                {
                    m_velocity.y = 0.f;
                    m_position.y = tile.GetShape().getPosition().y + m_shape.getSize().y;
                }

                if (yVel > 0)
                {
                    m_isGrounded = true;
                    m_velocity.y = 0.f;
                    m_position.y = tile.GetShape().getPosition().y - m_shape.getSize().y;
                }
            }
        }
    }

    void Player::Jump() { m_velocity.y = -1700.f; }

    void Player::Draw()
    {
        m_shape.setPosition(m_position);
        Renderer::Draw(m_shape);
    }
}
