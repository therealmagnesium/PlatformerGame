#pragma once
#include "Core/Base.h"

#include <SFML/Window/Keyboard.hpp>
#include <string>

namespace Engine
{
    class Input
    {
    public:
        static bool IsKeyDown(sf::Keyboard::Key key);
        static bool IsKeyTyped(sf::Keyboard::Key key);
        static s8 GetAxis(const std::string& axis, bool alt = false);

    public:
        static bool keyTyped;
        static bool keysDown[sf::Keyboard::KeyCount];
    };
}
