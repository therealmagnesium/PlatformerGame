#include "Scene/Tilemap.h"
#include "Scene/Tile.h"
#include "Core/Base.h"
#include "Core/Log.h"

#include <SFML/System/Vector2.hpp>

namespace Engine
{
    Tilemap::Tilemap()
    {
        m_numRows = 15;
        m_numCols = 50;
    }

    void Tilemap::AddTile(u32 gridX, u32 gridY)
    {
        Tile tile(TileType::Solid);

        sf::Vector2f position = sf::Vector2f(gridX * TILE_SIZE, gridY * TILE_SIZE);
        tile.SetPosition(position);

        m_tiles.push_back(tile);
    }

    void Tilemap::RemoveTile(u32 gridX, u32 gridY)
    {
        if (!m_tiles.empty())
        {
            for (u32 i = 0; i < m_tiles.size(); i++)
            {
                sf::Vector2f tilePosition = m_tiles[i].GetShape().getPosition();
                sf::Vector2f checkPosition = sf::Vector2f(gridX * TILE_SIZE, gridY * TILE_SIZE);
                if (tilePosition == checkPosition)
                {
                    LOG_INFO("Removing tile at grid <%f, %f>\n", V2_OPEN(tilePosition));
                    m_tiles.erase(m_tiles.begin() + i);
                }
            }
        }
    }

    void Tilemap::Draw()
    {
        for (u32 i = 0; i < m_tiles.size(); i++)
            m_tiles[i].Draw();
    }
}
