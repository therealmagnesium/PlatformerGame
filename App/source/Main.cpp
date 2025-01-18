#include "Game.h"

int main(int argc, char** argv)
{
    ApplicationSpecification appInfo;
    Game game(appInfo);
    game.Run();

    return 0;
}
