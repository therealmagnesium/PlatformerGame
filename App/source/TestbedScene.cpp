#include "TestbedScene.h"
#include "Core/AssetManager.h"
#include "Core/Log.h"
#include "Graphics/Renderer.h"
#include "PlayScene.h"

#include <Core/Application.h>
#include <Core/Input.h>
#include <Core/Math.h>

#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <cassert>
#include <cstdlib>

using namespace Engine;

static Application* app;
static AssetManager* assets;
static sf::Vector2f position;
static sf::Vector2f scale;

Testbed::Testbed()
{
    app = Application::Get();
    assets = AssetManager::Get();
    assert(assets);

    position = sf::Vector2f(0.f, 0.f);
    scale = sf::Vector2f(3.f, 3.f);

    m_sprite.setTexture(assets->GetTexture("playerIdle"));
    CenterOrigin(m_sprite, 11);

    m_animations[0] = Animation("idle", m_sprite, 11, 0.05f);
    m_animations[1] = Animation("run", m_sprite, 12, 0.04f);

    m_animController.AddAnimation(m_animations[0], assets->GetTexture("playerIdle"));
    m_animController.AddAnimation(m_animations[1], assets->GetTexture("playerRun"));
    m_animController.SwitchToAnim("idle");
}

void Testbed::OnUpdate()
{
    if (Input::IsKeyTyped(sf::Keyboard::E))
        app->SwitchToScene("Play", new PlayScene());

    s8 direction = Input::GetAxis("Horizontal");

    if (abs(direction) > 0)
    {
        m_animController.SwitchToAnim("run");
        scale.x = direction * 3.f;
    }
    else
    {
        m_animController.SwitchToAnim("idle");
    }

    m_animController.Update();
}

void Testbed::OnRender()
{
    m_sprite.setPosition(position);
    m_sprite.setScale(scale);
    Renderer::Draw(m_sprite);
}
