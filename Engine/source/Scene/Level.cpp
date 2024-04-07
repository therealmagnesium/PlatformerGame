#include "Scene/Level.h"
#include "Scene/Tile.h"
#include <SFML/System/Vector2.hpp>

namespace Engine
{
    Level::Level()
    {
        m_data.numRows = 0;
        m_data.numCols = 0;
        m_data.map = "";
    }

    void Level::Load(const LevelData& data)
    {
        m_data = data;

        for (u32 i = 0; i < m_data.numRows; i++)
        {
            for (u32 j = 0; j < m_data.numCols; j++)
            {
                char index = m_data.map[i * m_data.numCols + j];

                switch (index)
                {
                    case 'x':
                    {
                        Tile tile(TileType::Solid);
                        tile.SetPosition(sf::Vector2f(j * TILE_SIZE, i * TILE_SIZE));
                        m_data.tiles.push_back(tile);
                        break;
                    }
                    case 'o':
                    {
                        Tile tile(TileType::Water);
                        tile.SetPosition(sf::Vector2f(j * TILE_SIZE, i * TILE_SIZE));
                        m_data.tiles.push_back(tile);
                        break;
                    }
                    case 'p':
                    {
                        break;
                    }
                    default:
                        break;
                }
            }
        }
    }

    void Level::Draw()
    {
        for (u32 i = 0; i < m_data.tiles.size(); i++)
        {
            Tile& tile = m_data.tiles[i];
            tile.Draw();
        }
    }
}
