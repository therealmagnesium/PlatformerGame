#pragma once
#include <Graphics/Camera.h>
#include <Scene/Scene.h>
#include <Scene/Level.h>
#include <Scene/Player.h>

using namespace Engine;

class PlayScene : public Scene
{
public:
    PlayScene();

private:
    void OnUpdate() override;
    void OnRender() override;

private:
    Camera m_camera;
    Level m_level;
    Player m_player;
};
