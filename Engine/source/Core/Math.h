#pragma once
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>

namespace Engine
{
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
    bool CheckAABB(sf::FloatRect a, sf::FloatRect b);
}
