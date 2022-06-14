#include "Precompile.h"
#include "GameClasses.h"

int main()
{
    Game game;

    while (game.running())
    {
        game.update();
        game.render();
    }
}