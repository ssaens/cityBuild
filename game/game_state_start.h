//
// Created by Dillon Yao on 2/27/17.
//

#include <SFML/Graphics/View.hpp>
#include "game_state.h"
#include <utility>

#ifndef CITYBUILD_GAME_STATE_START_H
#define CITYBUILD_GAME_STATE_START_H

class GameStateStart : public GameState {
private:
    sf::View view;
    void loadGame();
    std::map<std::string, Gui> guiSystem;

public:
    GameStateStart(Game *game);

    virtual void draw(const float dt);
    virtual void update(const float dt);
    virtual void handleInput();
};

#endif //CITYBUILD_GAME_STATE_START_H
