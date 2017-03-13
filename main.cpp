#include <iostream>

#include "game/game.h"
#include "game/game_state_start.h"

int main() {
    Game game;

    game.pushState(new GameStateStart(&game));
    game.gameLoop();
    return 0;
}