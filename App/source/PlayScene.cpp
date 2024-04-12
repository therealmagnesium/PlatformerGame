#include "PlayScene.h"
#include "TestbedScene.h"

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

PlayScene::PlayScene()
{
    app = Application::Get();

    m_player.SetLevelHandle(&m_level);
    m_player.SetPosition(1000.f, 0.f);

    LevelData data;
    data.numRows = 15;
    data.numCols = 50;
    data.map = levelData;
    m_level.Load(data);

    m_camera.SetType(CameraType::PositionLock);
    m_camera.SetClearColor(sf::Color::Black);
    m_camera.SetPanSpeed(700.f);
    m_camera.SetTarget(m_player.GetPosition());
    this->SetMainCamera(&m_camera);
}

void PlayScene::OnUpdate()
{
    if (app->DebugEnabled())
    {
        if (Input::IsKeyTyped(sf::Keyboard::X))
            m_camera.LogPosition();
    }

    m_player.Update();
    m_camera.SetTarget(m_player.GetPosition());

    if (Input::IsKeyTyped(sf::Keyboard::E))
        app->SwitchToScene("Testbed", new Testbed());
}

void PlayScene::OnRender()
{
    m_level.Draw();
    m_player.Draw();
}
