#include "Graphics/Renderer.h"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include <assert.h>

namespace Engine
{
    Window* Renderer::s_window = NULL;
    Camera* Renderer::s_camera = NULL;

    void Renderer::Init(Window* window, Camera* camera)
    {
        assert(window);
        assert(camera);

        s_window = window;
        s_camera = camera;
    }

    void Renderer::Draw(sf::Drawable& drawable)
    {
        assert(s_window);
        sf::RenderWindow* nativeWindow = s_window->GetHandle();
        nativeWindow->draw(drawable);
    }

    void Renderer::Display()
    {
        assert(s_window);
        sf::RenderWindow* nativeWindow = s_window->GetHandle();
        nativeWindow->display();
    }
}
