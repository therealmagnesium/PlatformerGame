#pragma once

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>

#define TILE_SIZE 60

namespace Engine
{
    enum class TileType
    {
        None = 0,
        Solid,
        Water,
    };

    class Tile
    {
    public:
        Tile(TileType type);

        inline sf::RectangleShape& GetShape() { return m_shape; }

        inline void SetPosition(const sf::Vector2f& position) { m_shape.setPosition(position); }
        inline void SetFillColor(const sf::Color& color) { m_shape.setFillColor(color); }
        inline void SetOutlineColor(const sf::Color& color) { m_shape.setOutlineColor(color); }

        void Draw();

    private:
        TileType m_type;
        sf::RectangleShape m_shape;
    };
}
