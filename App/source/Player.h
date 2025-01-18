#pragma once
#include <Core/Base.h>
#include <Graphics/Tilemap.h>
#include <raylib.h>

using namespace Graphics;

struct Player
{
    Vector2 position;
    Vector2 velocity;
    Rectangle collisionBox;
    bool isJumping = false;
    u32 width = 64;
    u32 height = 64;
};

void UpdatePlayer(Player& player, Tilemap& tilemap);
void DrawPlayer(Player& player);
