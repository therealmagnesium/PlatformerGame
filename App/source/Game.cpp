#include "Game.h"

#include <Core/Application.h>
#include <Core/Base.h>
#include <Core/Log.h>
#include <Core/Math.h>
#include <Core/Input.h>

#include <Graphics/Camera.h>
#include <Graphics/Renderer.h>

#include <Scene/Tile.h>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <string>

static Application* app = NULL;

static std::string levelData = "x................................................x"
                               "x................................................x"
                               "x................................................x"
                               "x................................................x"
                               "x................................................x"
                               "x..............xxxxx.............................x"
                               "x................................................x"
                               "x......xxxxx.....................................x"
                               "x.xx.............................................x"
                               "x..x.............................................x"
                               "x................................................x"
                               "xxxxxxxxxxxxxxxxxxxxxxxxxxxxooooooooxxxxxxxxxxxxxx"
                               "xxxxxxxxxxxxxxxxxxxxxxxxxxxxooooooooxxxxxxxxxxxxxx"
                               "xxxxxxxxxxxxxxxxxxxxxxxxxxxxooooooooxxxxxxxxxxxxxx"
                               "xxxxxxxxxxxxxxxxxxxxxxxxxxxxooooooooxxxxxxxxxxxxxx";

Game::Game(const AppInfo& info) : Application(info)
{
    app = Application::Get();

    m_player.SetLevelHandle(&m_level);
    m_player.SetPosition(1000.f, 370.f);

    LevelData data;
    data.numRows = 15;
    data.numCols = 50;
    data.map = levelData;
    m_level.Load(data);

    m_camera.SetType(CameraType::HorizontalScroll);
    m_camera.SetClearColor(sf::Color::Black);
    m_camera.SetPanSpeed(700.f);
    app->SetMainCamera(&m_camera);
}

void Game::OnUpdate()
{
    if (!app->DebugEnabled())
        m_player.Update();
    else
    {
        if (Input::IsKeyTyped(sf::Keyboard::X))
            m_camera.LogPosition();
    }

    m_camera.SetTarget(m_player.GetShape().getPosition());
}

void Game::OnRender()
{
    m_level.Draw();
    m_player.Draw();
}
