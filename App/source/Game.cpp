#include "Game.h"

#include <Graphics/Tilemap.h>
#include <raylib.h>

using namespace Core;
using namespace Graphics;

Game::Game(const ApplicationSpecification& appInfo) : Application(appInfo)
{
    m_camera.target = {0.f, 0.f};
    m_camera.offset = {appInfo.windowWidth / 2.f, appInfo.windowHeight / 2.f};
    m_camera.zoom = 0.8f;
    m_camera.rotation = 0.f;
    this->SetPrimaryCamera(&m_camera);

    m_tilemap = LoadTilemap("assets/Test.tmx");

    m_player.position = {200.f, 200.f};
}

Game::~Game()
{
    UnloadTilemap(m_tilemap);
}

void Game::OnUpdate()
{
    UpdatePlayer(m_player, m_tilemap);
    m_camera.target = m_player.position;
    m_camera.target.y /= 1.2f;
}

void Game::OnRender()
{
    DrawTilemap(m_tilemap, 4.f);
    DrawPlayer(m_player);
}

void Game::OnRenderUI()
{
    DrawFPS(20, 20);
}
