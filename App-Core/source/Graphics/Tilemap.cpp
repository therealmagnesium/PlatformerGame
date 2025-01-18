#include "Graphics/Tilemap.h"
#include "Core/Base.h"

#include <tmx.h>
#include <raylib.h>

namespace Graphics
{
    static void* _CallbackTextureLoad(const char* path)
    {
        Texture2D* returnValue = new Texture2D;
        *returnValue = LoadTexture(path);
        return returnValue;
    }

    static void _CallbackTextureFree(void* ptr)
    {
        UnloadTexture(*((Texture2D*)ptr));
        free(ptr);
    }

    static void LoadAllLayers(Tilemap& tilemap, tmx_layer* layers)
    {
        while (layers != NULL)
        {
            if (layers->type == L_LAYER)
            {
                for (u32 i = 0; i < tilemap.height; i++)
                {
                    for (u32 j = 0; j < tilemap.width; j++)
                    {
                        Tile tile;
                        u32 gid = (layers->content.gids[i * tilemap.width + j]) & TMX_FLIP_BITS_REMOVAL;

                        if (tilemap.map->tiles[gid] != NULL)
                        {
                            tmx_tileset* tileset = tilemap.map->tiles[gid]->tileset;
                            tile.texture = (Texture2D*)tileset->image->resource_image;

                            tile.width = tileset->tile_width;
                            tile.height = tileset->tile_height;

                            tile.position.x = j * tile.width;
                            tile.position.y = i * tile.height;

                            tile.source.x = tilemap.map->tiles[gid]->ul_x;
                            tile.source.y = tilemap.map->tiles[gid]->ul_y;
                            tile.source.width = tile.width;
                            tile.source.height = tile.height;

                            tile.id = gid;

                            tilemap.tiles.push_back(tile);
                        }
                    }
                }
            }

            layers = layers->next;
        }
    }

    Tilemap LoadTilemap(const char* path)
    {
        tmx_img_load_func = _CallbackTextureLoad;
        tmx_img_free_func = _CallbackTextureFree;

        Tilemap tilemap;
        tilemap.map = tmx_load(path);
        if (tilemap.map == NULL)
        {
            TraceLog(LOG_WARNING, "Failed to load tilemap %s", path);
            return tilemap;
        }

        tilemap.width = tilemap.map->width;
        tilemap.height = tilemap.map->height;

        LoadAllLayers(tilemap, tilemap.map->ly_head);

        return tilemap;
    }

    void UnloadTilemap(Tilemap& tilemap)
    {
        if (tilemap.map != NULL)
            tmx_map_free(tilemap.map);
    }

    void DrawTilemap(Tilemap& tilemap, float scale)
    {
        for (Tile& tile : tilemap.tiles)
        {
            Rectangle dest;
            dest.x = tile.position.x * scale;
            dest.y = tile.position.y * scale;
            dest.width = tile.width * scale;
            dest.height = tile.height * scale;

            tile.collisionBox = dest;

            DrawTexturePro(*tile.texture, tile.source, dest, (Vector2){}, 0.f, WHITE);
            // DrawRectangleLinesEx(dest, 4.f, GREEN);
        }
    }
}
