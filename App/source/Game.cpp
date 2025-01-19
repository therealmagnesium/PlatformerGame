#include "Game.h"

#include <Graphics/Tilemap.h>
#include <raylib.h>

using namespace Core;
using namespace Graphics;

static Texture2D bgTexture;

Game::Game(const ApplicationSpecification& appInfo) : Application(appInfo)
{
    m_camera.target = {0.f, 0.f};
    m_camera.offset = {appInfo.windowWidth / 2.f, appInfo.windowHeight / 2.f};
    m_camera.zoom = 0.8f;
    m_camera.rotation = 0.f;
    this->SetPrimaryCamera(&m_camera);

    m_tilemap = LoadTilemap("assets/Test2.tmx");
    bgTexture = LoadTexture("assets/textures/sunnyland/Environments/Jungle/Layers/middle.png");

    m_player.position = {200.f, 200.f};
}

Game::~Game()
{
    UnloadTilemap(m_tilemap);
    UnloadTexture(bgTexture);
}

void Game::OnUpdate()
{
    UpdatePlayer(m_player, m_tilemap);
    m_camera.target = m_player.position;
    m_camera.target.y /= 1.2f;
}

void Game::OnRender()
{
    Rectangle source, dest;
    source.x = 0;
    source.y = 0;
    source.width = bgTexture.width;
    source.height = bgTexture.height;

    dest.x = -600.f;
    dest.y = -800.f;
    dest.width = this->GetSpecification().windowWidth * 4.f;
    dest.height = this->GetSpecification().windowHeight * 4.f;

    DrawTexturePro(bgTexture, source, dest, {}, 0.f, WHITE);

    DrawTilemap(m_tilemap, 4.f);
    DrawPlayer(m_player);
}

void Game::OnRenderUI()
{
    DrawFPS(20, 20);
}
