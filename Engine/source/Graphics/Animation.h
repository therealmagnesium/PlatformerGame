#pragma once
#include "Core/Base.h"

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <string>
#include <unordered_map>

namespace Engine
{
    class Animation
    {
    public:
        Animation();
        Animation(const std::string& name, sf::Sprite& sprite, u16 frameCount, float speed);

        inline std::string& GetName() { return m_name; }
        inline sf::Sprite* GetSprite() { return m_sprite; }

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

    class AnimationController
    {
    public:
        AnimationController();

        void Update();
        void AddAnimation(Animation& animation, sf::Texture& texture);
        void SwitchToAnim(const std::string& name);

    private:
        std::string m_animationIndex;
        std::unordered_map<std::string, Animation*> m_animations;
        std::unordered_map<std::string, const sf::Texture*> m_spriteSheets;
    };
}
