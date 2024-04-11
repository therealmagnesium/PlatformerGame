#include "Core/Application.h"
#include "Core/Input.h"
#include "Core/Log.h"
#include "Graphics/Camera.h"
#include "Graphics/Renderer.h"
#include "Scene/Scene.h"

#include <SFML/Window/Keyboard.hpp>
#include <cassert>
#include <cstddef>

namespace Engine
{
    Application* Application::s_instance = NULL;

    static Camera defaultCamera;
    static Scene* currentScene = NULL;
    static Camera* sceneCamera = NULL;

    Application::Application(const AppInfo& info) : m_info(info)
    {
        s_instance = this;

        m_window.Create(info);
        m_sceneIndex = "default";
    }

    Application::~Application()
    {
        for (auto [name, scene] : m_scenes)
            delete scene;
    }

    void Application::Run()
    {
        currentScene = m_scenes[m_sceneIndex];
        assert(currentScene);
        sceneCamera = currentScene->GetMainCamera();
        assert(sceneCamera);

        LOG_INFO("Application has started successfully");

        while (m_running)
        {
            m_window.HandleEvents();
            m_running = !m_window.ShouldClose();

            currentScene = m_scenes[m_sceneIndex];
            assert(currentScene);
            sceneCamera = currentScene->GetMainCamera();
            assert(sceneCamera);

            if (Input::IsKeyTyped(sf::Keyboard::Escape))
                m_running = false;

            if (Input::IsKeyDown(sf::Keyboard::LShift))
            {
                if (Input::IsKeyTyped(sf::Keyboard::C))
                    this->ToggleDebug();
            }

            sceneCamera->Update();
            currentScene->OnUpdate();

            sceneCamera->BeginScope();
            {
                currentScene->OnRender();
            }
            sceneCamera->EndScope();

            currentScene->OnRenderUI();

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

    void Application::SwitchToScene(const std::string& name, Scene* scene)
    {
        std::string prevIndex = m_sceneIndex;

        m_scenes[name] = scene;
        m_sceneIndex = name;

        LOG_INFO("Switched from scene %s -> %s", prevIndex.c_str(), m_sceneIndex.c_str());
    }
}
