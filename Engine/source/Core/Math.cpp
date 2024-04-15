#include "Core/Math.h"
#include "Core/Application.h"
#include "Core/Base.h"
#include "Core/Log.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/System/Vector2.hpp"
#include <math.h>

namespace Engine
{
    sf::Time Time::elapsed;
    float Time::deltaTime = 0.f;
    float Time::FPS = 0.f;

    float GetMagnitude(sf::Vector2f& v) { return sqrt(v.x * v.x + v.y * v.y); }

    void Normalize(sf::Vector2f& v)
    {
        float magnitude = GetMagnitude(v);

        if (magnitude > 0)
        {
            v.x /= magnitude;
            v.y /= magnitude;
        }
    }

    void LimitMagnitude(sf::Vector2f& v, float limit)
    {
        float magnitude = GetMagnitude(v);

        if (magnitude > limit)
        {
            Normalize(v);
            v *= limit;
        }
    }

    void CenterOrigin(sf::Sprite& sprite, u8 frameCount)
    {
        float xOffset = (sprite.getLocalBounds().width / 2.f) / frameCount;
        float yOffset = sprite.getLocalBounds().height / 2.f;

        sprite.setOrigin(xOffset, yOffset);
    }

    bool CheckAABB(sf::FloatRect a, sf::FloatRect b)
    {
        bool checkFromLeft = a.left + a.width > b.left;
        bool checkFromRight = a.left < b.left + b.width;
        bool checkFromTop = a.top + a.height > b.top;
        bool checkFromBottom = a.top < b.top + b.height;

        return checkFromLeft && checkFromRight && checkFromTop && checkFromBottom;
    }

    sf::Vector2i MapWorldToScreenCoords(sf::Vector2u& coord)
    {
        sf::Vector2i newCoord;
        sf::RenderWindow* nativeWindow = Application::Get()->GetWindow()->GetHandle();

        newCoord.x = coord.x - nativeWindow->getSize().x / 2;
        newCoord.y = coord.y - nativeWindow->getSize().y / 2;

        return newCoord;
    }
}
