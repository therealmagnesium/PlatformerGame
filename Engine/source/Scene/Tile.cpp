#include "Scene/Tile.h"
#include "Graphics/Renderer.h"

namespace Engine
{
    Tile::Tile(TileType type) : m_type(type)
    {
        m_shape.setPosition(0.f, 0.f);
        m_shape.setSize(sf::Vector2f(TILE_SIZE, TILE_SIZE));
        m_shape.setOutlineThickness(0.f);

        switch (m_type)
        {
            case TileType::Solid:
            {
                m_shape.setFillColor(sf::Color(127, 224, 145));
                m_shape.setOutlineColor(sf::Color(127, 224, 145));
                break;
            }

            case TileType::Water:
            {
                m_shape.setFillColor(sf::Color(44, 115, 153));
                m_shape.setOutlineColor(sf::Color(44, 115, 153));
                break;
            }

            default:
                break;
        }
    }

    void Tile::Draw() { Renderer::Draw(m_shape); }
}
