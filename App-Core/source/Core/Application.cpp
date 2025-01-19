#include "Application.h"
#include <raylib.h>

namespace Core
{
    static bool isInitialized = false;
    Application* App = NULL;

    Application::Application(const ApplicationSpecification& spec) : m_specification(spec)
    {
        if (isInitialized)
        {
            TraceLog(LOG_ERROR, "Application cannot be initialized more than once!");
            return;
        }

        App = this;
        InitWindow(m_specification.windowWidth, m_specification.windowHeight, m_specification.name.c_str());
        SetTargetFPS(60);
        SetExitKey(KEY_NULL);

        isInitialized = true;
    }

    Application::~Application()
    {
        CloseWindow();
    }

    void Application::Run()
    {
        if (!isInitialized)
        {
            TraceLog(LOG_FATAL, "Cannot run the application because it's not initialized!");
            this->Quit();
            return;
        }

        if (!m_primaryCamera)
        {
            TraceLog(LOG_FATAL, "Cannot run the application because no primary camera is set!");
            this->Quit();
            return;
        }

        while (m_isRunning)
        {
            m_isRunning = !WindowShouldClose();

            if (IsKeyPressed(KEY_ESCAPE))
                this->Quit();

            this->OnUpdate();

            BeginDrawing();
            {
                ClearBackground({35, 85, 65, 255});

                BeginMode2D(*m_primaryCamera);
                this->OnRender();
                EndMode2D();

                this->OnRenderUI();
            }
            EndDrawing();
        }

        this->OnShutdown();
    }

    void Application::Quit()
    {
        m_isRunning = false;
    }
}
