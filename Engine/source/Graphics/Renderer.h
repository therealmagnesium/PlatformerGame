#pragma once
#include "Graphics/Camera.h"
#include "Graphics/Window.h"
#include <SFML/Graphics/RenderTarget.hpp>

namespace Engine
{
    class Renderer
    {
    public:
        static void Init(Window* window, Camera* camera);
        static void Draw(sf::Drawable& drawable);
        static void Display();

    private:
        static Window* s_window;
        static Camera* s_camera;
    };
}
