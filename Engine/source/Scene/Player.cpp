#include "Scene/Player.h"
#include "Core/Input.h"
#include "Core/Log.h"
#include "Core/Math.h"
#include "Graphics/Renderer.h"
#include "Scene/Level.h"
#include "Scene/Tile.h"

#include <SFML/System/Vector2.hpp>
#include <cassert>

namespace Engine
{
    Player::Player()
    {
        m_shape.setPosition(0.f, 0.f);
        m_shape.setSize(sf::Vector2f(TILE_SIZE, TILE_SIZE));
        m_shape.setFillColor(sf::Color(14, 68, 82));
        m_shape.setOutlineColor(sf::Color(14, 68, 82));
        m_shape.setOutlineThickness(0.f);

        m_moveSpeed = 600.f;
    }

    void Player::Update()
    {
        sf::Vector2f inputAxis;
        inputAxis.x = Input::GetAxis("Horizontal");
        inputAxis.y = Input::GetAxis("Vertical");
        Normalize(inputAxis);

        m_velocity.x = m_moveSpeed * inputAxis.x;
        m_shape.move(m_velocity.x * Time::deltaTime, 0.f);
        this->HandleCollisions(m_velocity.x, 0.f);

        m_velocity.y = m_moveSpeed * inputAxis.y;
        m_shape.move(0.f, m_velocity.y * Time::deltaTime);
        this->HandleCollisions(0.f, m_velocity.y);
    }

    void Player::HandleCollisions(float xVel, float yVel)
    {
        assert(m_levelHandle);

        LevelData& levelData = m_levelHandle->GetData();
        Tile* tiles = levelData.tiles.data();
        u32 numTiles = levelData.tiles.size();

        for (u32 i = 0; i < numTiles; i++)
        {
            Tile& tile = tiles[i];

            if (CheckAABB(m_shape.getGlobalBounds(), tile.GetShape().getGlobalBounds()))
            {
                if (xVel < 0)
                {
                    m_velocity.x = 0.f;
                    m_shape.setPosition(tile.GetShape().getPosition().x + TILE_SIZE, m_shape.getPosition().y);
                }

                if (xVel > 0)
                {
                    m_velocity.x = 0.f;
                    m_shape.setPosition(tile.GetShape().getPosition().x - TILE_SIZE, m_shape.getPosition().y);
                }

                if (yVel < 0)
                {
                    m_velocity.y = 0.f;
                    m_shape.setPosition(m_shape.getPosition().x, tile.GetShape().getPosition().y + TILE_SIZE);
                }

                if (yVel > 0)
                {
                    m_velocity.y = 0.f;
                    m_shape.setPosition(m_shape.getPosition().x, tile.GetShape().getPosition().y - TILE_SIZE);
                }
            }
        }
    }

    void Player::Draw() { Renderer::Draw(m_shape); }
}
