#pragma once
#include <Graphics/Animation.h>
#include <Scene/Scene.h>
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
    sf::Texture m_texture;
    sf::Sprite m_sprite;
    Animation m_idleAnim;
};
