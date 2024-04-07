#include "Graphics/Window.h"
#include "Core/Application.h"
#include "Core/Input.h"
#include "Core/Math.h"
#include "Core/Log.h"

#include <SFML/Window/Event.hpp>

namespace Engine
{
    void Window::Create(const AppInfo& info)
    {
        m_handle.create(sf::VideoMode(info.screenWidth, info.screenHeight), info.name);

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

                default:
                    break;
            }
        }
    }
}
