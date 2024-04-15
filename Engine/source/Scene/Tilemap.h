#pragma once
#include "Core/Base.h"
#include "Scene/Tile.h"

#include <vector>

namespace Engine
{
    class Tilemap
    {
    public:
        Tilemap();

        void AddTile(u32 gridX, u32 gridY);
        void RemoveTile(u32 gridX, u32 gridY);
        void Draw();

    private:
        u32 m_numRows;
        u32 m_numCols;
        std::vector<Tile> m_tiles;
    };
}
