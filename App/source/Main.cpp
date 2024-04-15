#include "Game.h"
#include <Core/Base.h>
#include <Core/Log.h>

int main(int argc, char* argv[])
{
    AppInfo info;
    info.name = "Platformer!";
    info.author = "Magnus Ahlstromer V";
    info.version = 0.1;
    info.screenWidth = 1280;
    info.screenHeight = 720;
    info.targetFPS = 240;
    info.vsync = false;
    info.fullscreen = false;

    Game game(info);
    game.Run();

    return 0;
}
