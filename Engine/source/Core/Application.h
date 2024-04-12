#pragma once
#include "Core/AssetManager.h"
#include "Core/Base.h"
#include "Graphics/Window.h"
#include "Scene/Scene.h"

#include <string>
#include <unordered_map>

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
        bool fullscreen = false;
    };

    class Application
    {
    public:
        Application(const AppInfo& info);
        virtual ~Application();

        static inline Application* Get() { return s_instance; }

        inline bool DebugEnabled() { return m_debug; }
        inline AppInfo& GetInfo() { return m_info; }
        inline Window* GetWindow() { return &m_window; }
        inline Scene* GetCurrentScene() { return m_scenes[m_sceneIndex]; }

        void Run();
        void ToggleDebug();
        void SwitchToScene(const std::string& name, Scene* scene);

    protected:
        virtual void OnUpdate() = 0;
        virtual void OnRenderUI(){};

    private:
        bool m_debug = false;
        bool m_running = true;

        AppInfo m_info;
        Window m_window;

        std::string m_sceneIndex;
        std::unordered_map<std::string, Scene*> m_scenes;

        AssetManager m_assetManager;

    private:
        static Application* s_instance;
    };
}
