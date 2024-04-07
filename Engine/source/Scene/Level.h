#pragma once
#include "Core/Base.h"
#include "Scene/Tile.h"

#include <string>
#include <vector>

namespace Engine
{
    struct LevelData
    {
        u16 numRows;
        u16 numCols;
        std::string map;
        std::vector<Tile> tiles;
    };

    class Level
    {
    public:
        Level();

        inline LevelData& GetData() { return m_data; }

        void Load(const LevelData& data);
        void Draw();

    private:
        LevelData m_data;
    };
}
