#include "Scene/Scene.h"
#include "Graphics/Camera.h"

namespace Engine
{
    static Camera defaultCamera;

    Scene::Scene()
    {
        defaultCamera.SetClearColor(sf::Color(9, 30, 61));
        m_mainCamera = &defaultCamera;
    }
    Scene::~Scene() {}
}
