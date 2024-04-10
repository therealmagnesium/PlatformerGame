#pragma once
#include "Core/Base.h"

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <string>

namespace Engine
{
    class Animation
    {
    public:
        Animation();
        Animation(const std::string& name, sf::Sprite& sprite, u16 frameCount, float speed);

        inline void SetName(const std::string& name) { m_name = name; }
        inline void SetFrameCount(u16 frameCount) { m_frameCount = frameCount; }
        inline void SetSprite(sf::Sprite& sprite) { m_sprite = &sprite; }
        inline void SetSpeed(u8 speed) { m_speed = speed; }

        void Update();

    private:
        std::string m_name;
        sf::Sprite* m_sprite;
        u16 m_frameCount;
        u16 m_uvPosition;
        float m_speed;
        float m_totalTime;
    };
}
