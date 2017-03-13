//
// Created by Dillon Yao on 2/27/17.
//

#ifndef CITYBUILD_GAME_H
#define CITYBUILD_GAME_H

#include <SFML/Graphics.hpp>
#include <stack>
#include "texture_manager.h"
#include "../world/tile.h"
#include "gui.h"

class GameState;

class Game {
private:
    void loadTextures();
    void loadTiles();
    void loadStyles();
    void loadFonts();

public:
    Game();
    ~Game();

    const static unsigned int tileSize = 8;

    std::stack<GameState *> states;
    sf::RenderWindow window;

    TextureManager texmng;
    sf::Sprite background;

    std::map<std::string, Tile> tileAtlas;
    std::map<std::string, GuiStyle> stylesheets;
    std::map<std::string, sf::Font> fonts;

    void pushState(GameState *state);
    void popState();
    void changeState(GameState *state);
    GameState *peekState();

    void gameLoop();
};

#endif //CITYBUILD_GAME_H
