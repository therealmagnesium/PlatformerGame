#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>

namespace Engine
{
    struct AppInfo;

    class Window
    {
    public:
        Window() = default;

        inline bool ShouldClose() { return m_closed; }
        inline sf::RenderWindow* GetHandle() { return &m_handle; }

        void Create(const AppInfo& info);
        void HandleEvents();

    private:
        bool m_closed;
        sf::RenderWindow m_handle;
        sf::Clock m_deltaClock;
    };
}
