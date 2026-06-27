#ifndef NDEBUG
#include <vld.h>
#endif
#include "GameController.h"


int main(void)
{
    GameController* game = new GameController();
    
    game->RunMainLoop();

    delete game;

    return 0;
}