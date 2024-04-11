#pragma once
#include "Core/Base.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>

namespace Engine
{
    struct Transform
    {
        sf::Vector2f position;
        float rotation;
        sf::Vector2f scale;
    };

    struct CollisionBox
    {
        sf::FloatRect box;
        sf::Vector2f offset;
    };

    class Time
    {
    public:
        static sf::Time elapsed;
        static float deltaTime;
        static float FPS;
    };

    float GetMagnitude(sf::Vector2f& v);
    void Normalize(sf::Vector2f& v);
    void LimitMagnitude(sf::Vector2f& v, float limit);
    void CenterOrigin(sf::Sprite& sprite, u8 frameCount = 1);
    bool CheckAABB(sf::FloatRect a, sf::FloatRect b);
}
