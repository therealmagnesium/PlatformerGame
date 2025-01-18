#include "Player.h"
#include "raylib.h"
#include <Core/Application.h>
#include <Graphics/Tilemap.h>

using namespace Core;
using namespace Graphics;

enum class CollisionCheck
{
    Horizontal = 0,
    Vertical,
};

static void UpdateCollisionBox(Player& player)
{
    player.collisionBox.x = player.position.x;
    player.collisionBox.y = player.position.y;
    player.collisionBox.width = (float)player.width;
    player.collisionBox.height = (float)player.height;
}

static void HandleCollisions(Player& player, Tilemap& tilemap, CollisionCheck check)
{
    UpdateCollisionBox(player);

    for (u32 i = 0; i < tilemap.tiles.size(); i++)
    {
        Tile& tile = tilemap.tiles[i];

        if (CheckCollisionRecs(player.collisionBox, tile.collisionBox))
        {
            switch (check)
            {
                case CollisionCheck::Horizontal:
                {
                    if (player.velocity.x > 0.f)
                        player.position.x = tile.collisionBox.x - player.width;
                    if (player.velocity.x < 0.f)
                        player.position.x = tile.collisionBox.x + player.width;

                    player.velocity.x = 0.f;

                    break;
                }

                case CollisionCheck::Vertical:
                {
                    if (player.velocity.y > 0.f)
                        player.position.y = tile.collisionBox.y - player.height;
                    if (player.velocity.y < 0.f)
                        player.position.y = tile.collisionBox.y + player.height;

                    player.velocity.y = 0.f;
                    break;
                }
            }
        }
    }
}

void UpdatePlayer(Player& player, Tilemap& tilemap)
{
    const ApplicationSpecification& appInfo = App->GetSpecification();
    float direction = IsKeyDown(KEY_RIGHT) - IsKeyDown(KEY_LEFT);

    if (IsKeyPressed(KEY_UP) && !player.isJumping)
        player.isJumping = true;

    player.position.x += player.velocity.x;
    HandleCollisions(player, tilemap, CollisionCheck::Horizontal);
    player.velocity.x = direction * 15.f;

    player.position.y += player.velocity.y;
    HandleCollisions(player, tilemap, CollisionCheck::Vertical);

    if (player.isJumping && player.velocity.y == 0.f)
    {
        player.velocity.y -= 40.f;
        player.isJumping = false;
    }
    player.velocity.y += 3.f;

    UpdateCollisionBox(player);
}

void DrawPlayer(Player& player)
{
    DrawRectangleV(player.position, {(float)player.width, (float)player.height}, RED);
    // DrawRectangleLinesEx(player.collisionBox, 6.f, BLUE);
}
