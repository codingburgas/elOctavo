#include "Precompile.h"
#include "GameClass.h"

int main()
{
    Game game;

    while (game.running())
    {
        game.update();
        game.render();
    }
}