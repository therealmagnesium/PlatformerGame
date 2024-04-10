#include "TestbedScene.h"
#include "Graphics/Renderer.h"
#include "PlayScene.h"

#include <Core/Application.h>
#include <Core/Input.h>

#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>

using namespace Engine;

static Application* app = NULL;
static sf::Vector2f position;

Testbed::Testbed()
{
    app = Application::Get();

    position = sf::Vector2f(0.f, 0.f);

    m_texture.loadFromFile("assets/textures/player/idle.png");
    m_sprite.setTexture(m_texture);
    m_sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));

    m_idleAnim = Animation("idle", m_sprite, 11, 0.05f);
}

void Testbed::OnUpdate()
{
    if (Input::IsKeyTyped(sf::Keyboard::E))
        app->SwitchToScene("Play", new PlayScene());

    m_idleAnim.Update();
}

void Testbed::OnRender()
{
    m_sprite.setPosition(position);
    m_sprite.setScale(sf::Vector2f(3.f, 3.f));
    Renderer::Draw(m_sprite);
}
