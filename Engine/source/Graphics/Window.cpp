#include "Graphics/Window.h"
#include "Core/Application.h"
#include "Core/Input.h"
#include "Core/Math.h"
#include "Core/Log.h"
#include "SFML/System/Vector2.hpp"
#include "SFML/Window/WindowStyle.hpp"

#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>

namespace Engine
{
    void Window::Create(const AppInfo& info)
    {
        u32 style = sf::Style::Default;
        sf::VideoMode desktop = sf::VideoMode::getDesktopMode();

        if (info.fullscreen)
            style = sf::Style::Fullscreen;

        m_handle.create(desktop, info.name, style);

        if (info.vsync)
            m_handle.setVerticalSyncEnabled(true);
        else
            m_handle.setFramerateLimit(info.targetFPS);

        m_closed = false;
    }

    void Window::HandleEvents()
    {
        Time::elapsed = m_deltaClock.restart();
        Time::deltaTime = Time::elapsed.asSeconds();
        Time::FPS = 1.f / Time::deltaTime;

        Input::keyTyped = false;

        sf::Event event;
        while (m_handle.pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::Closed:
                {
                    m_closed = true;
                    m_handle.close();
                    break;
                }

                case sf::Event::KeyPressed:
                {
                    bool keyCheck = Input::keysDown[event.key.code];
                    Input::keyTyped = (keyCheck) ? false : true;
                    Input::keysDown[event.key.code] = true;

                    break;
                }

                case sf::Event::KeyReleased:
                {
                    Input::keyTyped = false;
                    Input::keysDown[event.key.code] = false;

                    break;
                }

                case sf::Event::Resized:
                {
                    sf::Vector2u newSize;
                    newSize.x = event.size.width;
                    newSize.y = event.size.height;

                    m_handle.setSize(newSize);

                    LOG_INFO("Window resized to %dx%d", newSize.x, newSize.y);
                    break;
                }

                default:
                    break;
            }
        }
    }
}
