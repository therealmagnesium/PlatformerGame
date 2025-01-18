#pragma once
#include "Core/Base.h"

#include <raylib.h>
#include <string>

namespace Core
{
    struct ApplicationSpecification
    {
        std::string name = "Untitled";
        std::string version = "1.0-dev";
        std::string author = "No author specified";

        u32 windowWidth = 1280;
        u32 windowHeight = 720;

        bool isVsyncEnabled = true;
    };

    class Application
    {
    public:
        Application() = default;
        Application(const ApplicationSpecification& spec);
        ~Application();

        void Run();
        void Quit();

        inline const ApplicationSpecification& GetSpecification() const { return m_specification; }
        inline const Camera2D* GetPrimaryCamera() { return m_primaryCamera; }

        inline void SetPrimaryCamera(Camera2D* camera) { m_primaryCamera = camera; }

    protected:
        virtual void OnUpdate() {}
        virtual void OnRender() {}
        virtual void OnRenderUI() {}
        virtual void OnShutdown() {}

    private:
        bool m_isRunning = true;
        ApplicationSpecification m_specification;
        Camera2D* m_primaryCamera = NULL;
    };

    extern Application* App;
}
