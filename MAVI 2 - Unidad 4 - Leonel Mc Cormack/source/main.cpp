#ifndef NDEBUG
#include <vld.h>
#endif
#include "GameController.h"


int main(void)
{
    GameController game;
    game.RunMainLoop();

    return 0;
}