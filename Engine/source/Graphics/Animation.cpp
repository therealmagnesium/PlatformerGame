#include "Graphics/Animation.h"
#include "Core/Base.h"
#include "Core/Log.h"
#include "Core/Math.h"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <cassert>
#include <cmath>

namespace Engine
{
    Animation::Animation()
    {
        m_name = "defaultName";
        m_frameCount = 1;
        m_speed = 10.f;
    }

    Animation::Animation(const std::string& name, sf::Sprite& sprite, u16 frameCount, float speed)
        : m_name(name), m_sprite(&sprite), m_frameCount(frameCount), m_speed(speed)
    {
        assert(m_sprite->getTexture());

        sf::Vector2u size = m_sprite->getTexture()->getSize();
        m_sprite->setTextureRect(sf::IntRect(0, 0, size.x, size.y));

        m_uvPosition = 0;
        m_totalTime = 0.f;
    }

    void Animation::Update()
    {
        m_totalTime += Time::deltaTime;
        if (m_totalTime >= m_speed)
        {
            m_totalTime -= m_speed;
            m_uvPosition++;

            if (m_uvPosition >= m_frameCount)
                m_uvPosition = 0;
        }

        assert(m_sprite->getTexture());
        const sf::Texture* texture = m_sprite->getTexture();
        sf::Vector2i size = sf::Vector2i(texture->getSize().x / m_frameCount, texture->getSize().y);
        sf::IntRect rect = {m_uvPosition * size.x, 0, size.x, size.y};

        m_sprite->setTextureRect(rect);
    }
}
