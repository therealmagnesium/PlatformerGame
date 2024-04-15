#pragma once
#include "Core/Base.h"

#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <string>

namespace Engine
{
    class Input
    {
    public:
        static bool IsKeyDown(sf::Keyboard::Key key);
        static bool IsKeyTyped(sf::Keyboard::Key key);
        static s8 GetAxis(const std::string& axis, bool alt = false);

        static bool IsMouseDown(sf::Mouse::Button button);
        static bool IsMouseClicked(sf::Mouse::Button button);
        static sf::Vector2u& GetMousePosition();

    public:
        static bool keyTyped;
        static bool keysDown[sf::Keyboard::KeyCount];

        static bool mouseClicked;
        static bool mouseButtonsDown[sf::Mouse::ButtonCount];
        static sf::Vector2u mousePosition;
    };
}
