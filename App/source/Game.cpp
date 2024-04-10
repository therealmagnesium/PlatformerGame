#include "Game.h"
#include "PlayScene.h"

#include <Core/Application.h>
#include <Core/Base.h>
#include <Core/Log.h>
#include <Core/Math.h>
#include <Core/Input.h>

Game::Game(const AppInfo& info) : Application(info) { this->SwitchToScene("Play", new PlayScene()); }

void Game::OnUpdate() {}
void Game::OnRenderUI() {}
