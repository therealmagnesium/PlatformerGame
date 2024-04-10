#pragma once
#include "Graphics/Camera.h"

namespace Engine
{
    class Scene
    {
    public:
        Scene();
        virtual ~Scene();

        inline Camera* GetMainCamera() { return m_mainCamera; }
        inline void SetMainCamera(Camera* camera) { m_mainCamera = camera; }

        virtual void OnUpdate() = 0;
        virtual void OnRender() = 0;
        virtual void OnRenderUI(){};

    private:
        Camera* m_mainCamera;
    };
}
