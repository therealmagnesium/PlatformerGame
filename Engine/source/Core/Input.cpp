#include "Core/Input.h"
#include "Core/Log.h"

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <string>

namespace Engine
{
    bool Input::keyTyped = false;
    bool Input::keysDown[sf::Keyboard::KeyCount]{0};

    bool Input::mouseClicked = false;
    bool Input::mouseButtonsDown[sf::Mouse::ButtonCount]{0};
    sf::Vector2u Input::mousePosition;

    bool Input::IsKeyDown(sf::Keyboard::Key key) { return keysDown[key]; }
    bool Input::IsKeyTyped(sf::Keyboard::Key key) { return keysDown[key] && keyTyped; }

    bool Input::IsMouseDown(sf::Mouse::Button button) { return mouseButtonsDown[button]; }
    bool Input::IsMouseClicked(sf::Mouse::Button button) { return mouseButtonsDown[button] && mouseClicked; }
    sf::Vector2u& Input::GetMousePosition() { return mousePosition; }

    s8 Input::GetAxis(const std::string& axis, bool alt)
    {
        s8 val = 0;

        if (axis == "Horizontal")
        {
            if (!alt)
                val = IsKeyDown(sf::Keyboard::Right) - IsKeyDown(sf::Keyboard::Left);
            else
                val = IsKeyDown(sf::Keyboard::D) - IsKeyDown(sf::Keyboard::A);
        }
        else if (axis == "Vertical")
        {
            if (!alt)
                val = IsKeyDown(sf::Keyboard::Down) - IsKeyDown(sf::Keyboard::Up);
            else
                val = IsKeyDown(sf::Keyboard::S) - IsKeyDown(sf::Keyboard::W);
        }
        else
        {
            LOG_WARN("%s is not a valid input axis", axis.c_str());
        }

        return val;
    }
}
