#include "Scene/Player.h"
#include "Core/Application.h"
#include "Core/Base.h"
#include "Core/Input.h"
#include "Core/Log.h"
#include "Core/Math.h"
#include "Graphics/Animation.h"
#include "Graphics/Renderer.h"
#include "Scene/Level.h"
#include "Scene/Tile.h"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <cassert>
#include <cstdlib>

namespace Engine
{
    static sf::Texture idleTexture;
    static sf::Texture runTexture;
    static Application* app;

    Player::Player()
    {
        app = Application::Get();

        m_transform.position = sf::Vector2f(0.f, 0.f);
        m_transform.scale = sf::Vector2f(3.f, 3.f);
        m_velocity = sf::Vector2f(0.f, 0.f);

        m_collisionBox.box = sf::FloatRect(0.f, 0.f, 50.f, 70.f);
        m_collisionBox.offset = sf::Vector2f(-25.f, -25.f);

        m_moveSpeed = 700.f;
        m_isGrounded = false;

        idleTexture.loadFromFile("assets/textures/player/idle.png");
        runTexture.loadFromFile("assets/textures/player/run.png");

        m_sprite.setTexture(idleTexture);
        m_sprite.setOrigin(16.f, 16.f);

        m_animations[PLAYER_IDLE] = Animation("idle", m_sprite, 11, 0.05f);
        m_animations[PLAYER_RUN] = Animation("run", m_sprite, 12, 0.04f);

        m_animController.AddAnimation(m_animations[PLAYER_IDLE], idleTexture);
        m_animController.AddAnimation(m_animations[PLAYER_RUN], runTexture);
        m_animController.SwitchToAnim("idle");
    }

    void Player::Update()
    {
        s8 direction = Input::GetAxis("Horizontal");
        this->HandleMovement(direction);
        this->HandleAnimation(direction);
    }

    void Player::HandleAnimation(s8 direction)
    {
        if (abs(direction) > 0)
        {
            m_animController.SwitchToAnim("run");
            m_transform.scale.x = direction * 3.f;
        }
        else
            m_animController.SwitchToAnim("idle");

        m_animController.Update();
    }

    void Player::HandleMovement(s8 direction)
    {
        if (Input::IsKeyTyped(sf::Keyboard::Up) && m_isGrounded)
            this->Jump();

        m_velocity.x = m_moveSpeed * direction;
        m_transform.position.x += m_velocity.x * Time::deltaTime;
        this->HandleCollisions(m_velocity.x, 0.f);

        m_transform.position.y += m_velocity.y * Time::deltaTime;
        this->HandleCollisions(0.f, m_velocity.y);
        m_velocity.y += GRAVITY * m_moveSpeed * Time::deltaTime;
    }

    void Player::HandleCollisions(float xVel, float yVel)
    {
        assert(m_levelHandle);

        LevelData& levelData = m_levelHandle->GetData();
        Tile* tiles = levelData.tiles.data();
        u32 numTiles = levelData.tiles.size();
        m_isGrounded = false;

        m_collisionBox.box.left = m_transform.position.x + m_collisionBox.offset.x;
        m_collisionBox.box.top = m_transform.position.y + m_collisionBox.offset.y;

        for (u32 i = 0; i < numTiles; i++)
        {
            Tile& tile = tiles[i];

            if (CheckAABB(m_collisionBox.box, tile.GetShape().getGlobalBounds()))
            {
                if (xVel < 0)
                {
                    float tileX = tile.GetShape().getPosition().x;
                    float sizeFactor = m_collisionBox.box.width - TILE_SIZE;
                    float finalCboxWidth = m_collisionBox.box.width - m_collisionBox.offset.x;
                    m_velocity.x = 0.f;
                    m_transform.position.x = tileX - sizeFactor + finalCboxWidth;
                }

                if (xVel > 0)
                {
                    float tileX = tile.GetShape().getPosition().x;
                    float sizeFactor = m_collisionBox.box.width + TILE_SIZE;
                    float finalCboxWidth = m_collisionBox.box.width - m_collisionBox.offset.x;

                    m_velocity.x = 0.f;
                    m_transform.position.x = tileX - sizeFactor + finalCboxWidth;
                }

                if (yVel < 0)
                {
                    m_velocity.y = 0.f;
                    m_transform.position.y =
                        tile.GetShape().getPosition().y + m_collisionBox.box.height - m_collisionBox.offset.y;
                }

                if (yVel > 0)
                {
                    m_isGrounded = true;
                    m_velocity.y = 0.f;
                    m_transform.position.y =
                        tile.GetShape().getPosition().y - m_collisionBox.box.height - m_collisionBox.offset.y;
                }
            }
        }
    }

    void Player::Jump() { m_velocity.y = -1700.f; }

    void Player::Draw()
    {
        m_sprite.setPosition(m_transform.position);
        m_sprite.setScale(m_transform.scale);
        Renderer::Draw(m_sprite);

        if (app->DebugEnabled())
            Renderer::Draw(m_collisionBox.box, sf::Color::Red);
    }
}
