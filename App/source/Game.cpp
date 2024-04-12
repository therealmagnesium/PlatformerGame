#include "Game.h"
#include "PlayScene.h"

#include <Core/Application.h>
#include <Core/AssetManager.h>
#include <Core/Base.h>
#include <Core/Log.h>
#include <Core/Math.h>
#include <Core/Input.h>

static AssetManager* assets;

Game::Game(const AppInfo& info) : Application(info)
{
    assets = AssetManager::Get();
    this->LoadAssets();
    this->SwitchToScene("Play", new PlayScene());
}

void Game::OnUpdate() {}
void Game::OnRenderUI() {}

void Game::LoadAssets()
{
    assets->AddTexture("playerIdle", "assets/textures/player/idle.png");
    assets->AddTexture("playerRun", "assets/textures/player/run.png");
}
