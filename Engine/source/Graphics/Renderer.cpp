#include "Graphics/Renderer.h"
#include "Core/Application.h"
#include "Core/Base.h"
#include "Core/Log.h"
#include "Core/Math.h"
#include "Graphics/Camera.h"

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include <SFML/Graphics/Shape.hpp>
#include <SFML/System/Vector2.hpp>
#include <assert.h>

namespace Engine
{
    static Application* app = NULL;

    void Renderer::Draw(sf::Shape& drawable)
    {
        app = Application::Get();
        assert(app);

        sf::RenderWindow* nativeWindow = app->GetWindow()->GetHandle();
        Camera* camera = app->GetCamera();

        sf::FloatRect cameraArea;
        cameraArea.width = camera->GetView().getSize().x;
        cameraArea.height = camera->GetView().getSize().y;
        cameraArea.left = camera->GetView().getCenter().x - cameraArea.width / 2.f;
        cameraArea.top = camera->GetView().getCenter().y - cameraArea.height / 2.f;

        if (CheckAABB(cameraArea, drawable.getGlobalBounds()))
            nativeWindow->draw(drawable);
    }

    void Renderer::Display()
    {
        app = Application::Get();
        assert(app);

        sf::RenderWindow* nativeWindow = app->GetWindow()->GetHandle();
        nativeWindow->display();
    }
}
