#pragma once
#include "Core/Base.h"
#include "Graphics/Camera.h"
#include "Graphics/Window.h"

#include <string>

namespace Engine
{
    struct AppInfo
    {
        std::string name;
        std::string author;
        float version;
        u32 screenWidth;
        u32 screenHeight;
        u16 targetFPS;
        bool vsync = true;
    };

    class Application
    {
    public:
        Application(const AppInfo& info);

        static inline Application* Get() { return s_instance; }

        inline bool DebugEnabled() { return m_debug; }
        inline AppInfo& GetInfo() { return m_info; }
        inline Camera* GetCamera() { return m_mainCamera; }
        inline Window* GetWindow() { return &m_window; }

        inline void SetMainCamera(Camera* camera) { m_mainCamera = camera; }

        void Run();
        void ToggleDebug();

    protected:
        virtual void OnUpdate() = 0;
        virtual void OnRender() = 0;
        virtual void OnRenderUI(){};

    private:
        bool m_debug = false;
        bool m_running = true;

        AppInfo m_info;
        Window m_window;
        Camera* m_mainCamera;

    private:
        static Application* s_instance;
    };
}
