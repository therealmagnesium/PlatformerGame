#include "TestbedScene.h"
#include "Core/AssetManager.h"
#include "Core/Base.h"
#include "Core/Log.h"
#include "Graphics/Renderer.h"
#include "PlayScene.h"
#include "Scene/Tile.h"

#include <Core/Application.h>
#include <Core/Input.h>
#include <Core/Math.h>

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <cassert>

using namespace Engine;

static Application* app;
static AssetManager* assets;
static sf::FloatRect rect;

Testbed::Testbed()
{
    app = Application::Get();
    assets = AssetManager::Get();

    assert(app);
    assert(assets);

    m_camera.SetType(CameraType::Static);
    m_camera.SetClearColor(sf::Color::Black);
    m_camera.SetPanSpeed(700.f);
    this->SetMainCamera(&m_camera);
}

void Testbed::OnUpdate()
{
    sf::Vector2i rectToScreen = MapWorldToScreenCoords(Input::GetMousePosition());

    rect.left = rectToScreen.x;
    rect.top = rectToScreen.y;
    rect.width = TILE_SIZE;
    rect.height = TILE_SIZE;

    if (Input::IsMouseClicked(sf::Mouse::Left))
    {
        sf::Vector2i clickPosition = MapWorldToScreenCoords(Input::GetMousePosition());
        m_tilemap.AddTile(clickPosition.x / TILE_SIZE, clickPosition.y / TILE_SIZE);
    }
}

void Testbed::OnRender()
{
    m_tilemap.Draw();

    Renderer::Draw(rect, sf::Color::Green);
    Renderer::Draw(m_sprite);
}
