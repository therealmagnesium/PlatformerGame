#pragma once
#include "Graphics/Camera.h"
#include "Graphics/Window.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Shape.hpp>

namespace Engine
{
    class Renderer
    {
    public:
        static void Draw(sf::Shape& drawable);
        static void Display();

    private:
    };
}
