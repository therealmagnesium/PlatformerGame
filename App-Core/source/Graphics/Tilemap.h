#pragma once
#include "Core/Base.h"

#include <tmx.h>
#include <raylib.h>
#include <vector>

namespace Graphics
{
    struct Tile
    {
        u32 id = 0;
        Vector2 position = {0.f, 0.f};
        u32 width = 0;
        u32 height = 0;
        Rectangle source;
        Rectangle collisionBox;
        Texture2D* texture = NULL;
    };

    struct Tilemap
    {
        tmx_map* map = NULL;
        u32 width = 0;
        u32 height = 0;
        std::vector<Tile> tiles;
    };

    Tilemap LoadTilemap(const char* path);
    void UnloadTilemap(Tilemap& tilemap);
    void DrawTilemap(Tilemap& tilemap, float scale);
}
