#pragma once
#include <Core/Application.h>

#include <Graphics/Camera.h>
#include <Graphics/Window.h>

#include <Scene/Level.h>
#include <Scene/Player.h>

using namespace Engine;

class Game : public Application
{
public:
    Game(const AppInfo& info);

private:
    void OnUpdate() override;
    void OnRender() override;

private:
    Camera m_camera;
    Level m_level;
    Player m_player;
};
