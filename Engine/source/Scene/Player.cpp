#include "Scene/Player.h"
#include "Core/Input.h"
#include "Core/Log.h"
#include "Core/Math.h"
#include "Graphics/Renderer.h"
#include "Scene/Level.h"
#include "Scene/Tile.h"

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
        sf::Vector2f inputAxis = this->HandleControls();
        this->HandleMovement(inputAxis);
    }

    sf::Vector2f Player::HandleControls()
    {
        sf::Vector2f inputAxis;
        inputAxis.x = Input::GetAxis("Horizontal");
        inputAxis.y = Input::GetAxis("Vertical");
        Normalize(inputAxis);

        return inputAxis;
    }

    void Player::HandleMovement(const sf::Vector2f& inputAxis)
    {

        if (Input::IsKeyTyped(sf::Keyboard::Up) && m_isGrounded)
            this->Jump();

        m_position.x += m_velocity.x * Time::deltaTime;
        this->HandleCollisions(m_velocity.x, 0.f);
        m_velocity.x = m_moveSpeed * inputAxis.x;

        m_position.y += m_velocity.y * Time::deltaTime;
        this->HandleCollisions(0.f, m_velocity.y);
        m_velocity.y += 25.f;
    }

    void Player::HandleCollisions(float xVel, float yVel)
    {
        assert(m_levelHandle);

        m_shape.setPosition(m_position);

        LevelData& levelData = m_levelHandle->GetData();
        Tile* tiles = levelData.tiles.data();
        u32 numTiles = levelData.tiles.size();
        m_isGrounded = false;

        for (u32 i = 0; i < numTiles; i++)
        {
            Tile& tile = tiles[i];

            if (CheckAABB(m_shape.getGlobalBounds(), tile.GetShape().getGlobalBounds()))
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

    void Player::Draw() { Renderer::Draw(m_shape); }
}
