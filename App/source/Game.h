#pragma once
#include "Player.h"

#include <Core/Application.h>
#include <Graphics/Tilemap.h>
#include <raylib.h>

using namespace Core;
using namespace Graphics;

class Game : public Application
{
public:
    Game(const ApplicationSpecification& appInfo);
    ~Game();

    void OnUpdate() override;
    void OnRender() override;
    void OnRenderUI() override;

private:
    Player m_player;
    Tilemap m_tilemap;
    Camera2D m_camera;
};
