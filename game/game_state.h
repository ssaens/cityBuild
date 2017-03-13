//
// Created by Dillon Yao on 2/27/17.
//

#ifndef CITYBUILD_GAME_STATE_H
#define CITYBUILD_GAME_STATE_H


#include "game.h"

class GameState {
public:
    Game *game;
    virtual void draw(const float dt) = 0;
    virtual void update(const float dt) = 0;
    virtual void handleInput() = 0;
};


#endif //CITYBUILD_GAME_STATE_H
