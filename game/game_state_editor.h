//
// Created by Dillon Yao on 2/27/17.
//

#ifndef CITYBUILD_GAME_STATE_EDITOR_H
#define CITYBUILD_GAME_STATE_EDITOR_H

#include "game_state.h"
#include "../world/City.h"

enum class ActionState { NONE, PANNING, SELECTING };

class GameStateEditor : public GameState {
private:
    ActionState actionState;

    sf::Vector2i panningAnchor;
    float zoomLevel;

    sf::View gameView;
    sf::View guiView;
    City city;

    sf::Vector2i selectionStart;
    sf::Vector2i selectionEnd;

    Tile *currentTile;

    std::map<std::string, Gui> guiSystem;
    void loadGui();

public:
    GameStateEditor(Game *game);

    virtual void draw(const float dt);
    virtual void update(const float dt);
    virtual void handleInput();
};

#endif //CITYBUILD_GAME_STATE_EDITOR_H
