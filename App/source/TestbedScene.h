#pragma once
#include "Graphics/Camera.h"
#include <Graphics/Animation.h>
#include <Scene/Scene.h>
#include <Scene/Tilemap.h>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

using namespace Engine;

class Testbed : public Scene
{
public:
    Testbed();

    void OnUpdate() override;
    void OnRender() override;

private:
    sf::Sprite m_sprite;

    Animation m_animations[2];
    AnimationController m_animController;

    Camera m_camera;

    Tilemap m_tilemap;
};
