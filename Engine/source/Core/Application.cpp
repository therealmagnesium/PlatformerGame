#include "Core/Application.h"
#include "Core/Input.h"
#include "Core/Log.h"
#include "Graphics/Camera.h"
#include "Graphics/Renderer.h"
#include <SFML/Window/Keyboard.hpp>

namespace Engine
{
    Application* Application::s_instance = NULL;
    static Camera defaultCamera;

    Application::Application(const AppInfo& info) : m_info(info)
    {
        s_instance = this;

        m_window.Create(info);

        m_mainCamera = &defaultCamera;
        Renderer::Init(&m_window, m_mainCamera);
    }

    void Application::Run()
    {
        while (m_running)
        {
            m_window.HandleEvents();
            m_running = !m_window.ShouldClose();

            if (Input::IsKeyTyped(sf::Keyboard::Escape))
                m_running = false;

            if (Input::IsKeyDown(sf::Keyboard::LShift))
            {
                if (Input::IsKeyTyped(sf::Keyboard::D))
                    this->ToggleDebug();
            }

            this->OnUpdate();
            m_mainCamera->Update();

            m_mainCamera->BeginScope();
            this->OnRender();
            m_mainCamera->EndScope();

            this->OnRenderUI();

            Renderer::Display();
        }
    }

    void Application::ToggleDebug()
    {
        m_debug = !m_debug;

        if (m_debug)
            LOG_INFO("Debug mode enabled");
        else
            LOG_INFO("Debug mode disabled");
    }
}
