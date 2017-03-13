//
// Created by Dillon Yao on 2/27/17.
//

#include "game.h"
#include "game_state.h"

Game::Game() {
    this->loadTextures();
    this->loadTiles();
    this->loadFonts();
    this->loadStyles();

    window.create(sf::VideoMode(800, 600), "CityBuild");
    window.setFramerateLimit(60);

    this->background.setTexture(this->texmng.getRef("background"));
}

Game::~Game() {
    while (!states.empty()) {
        popState();
    }
}

void Game::pushState(GameState *state) {
    states.push(state);
}

void Game::popState() {
    delete states.top();
    states.pop();
}

void Game::changeState(GameState *state) {
    if (!states.empty()) {
        popState();
    }
    pushState(state);
}

GameState *Game::peekState() {
    if (states.empty()) {
        return nullptr;
    }
    return states.top();
}

void Game::gameLoop() {
    sf::Clock clock;

    while (window.isOpen()) {
        sf::Time elapsed = clock.restart();
        float dt = elapsed.asSeconds();

        if (peekState() == nullptr) continue;
        peekState()->handleInput();
        peekState()->update(dt);
        window.clear(sf::Color::Black);
        peekState()->draw(dt);
        window.display();
    }
}


void Game::loadTextures() {
    texmng.loadTexture("background",    "./media/background.png");
    texmng.loadTexture("grass",         "./media/grass.png");
    texmng.loadTexture("forest",        "./media/forest.png");
    texmng.loadTexture("water",         "./media/water.png");
    texmng.loadTexture("residential",   "./media/residential.png");
    texmng.loadTexture("commercial",    "./media/commercial.png");
    texmng.loadTexture("industrial",    "./media/industrial.png");
    texmng.loadTexture("road",          "./media/road.png");
}

void Game::loadTiles() {
    Animation staticAnimation(0, 0, 1.0f);
    this->tileAtlas["grass"] =
            Tile(this->tileSize, 1, texmng.getRef("grass"),
                 { staticAnimation },
                 TileType::GRASS, 50, 0, 1);
    tileAtlas["forest"] =
            Tile(this->tileSize, 1, texmng.getRef("forest"),
                 { staticAnimation },
                 TileType::FOREST, 100, 0, 1);
    tileAtlas["water"] =
            Tile(this->tileSize, 1, texmng.getRef("water"),
                 { Animation(0, 3, 0.5f),
                   Animation(0, 3, 0.5f),
                   Animation(0, 3, 0.5f) },
                 TileType::WATER, 0, 0, 1);
    tileAtlas["residential"] =
            Tile(this->tileSize, 2, texmng.getRef("residential"),
                 { staticAnimation, staticAnimation, staticAnimation,
                   staticAnimation, staticAnimation, staticAnimation },
                 TileType::RESIDENTIAL, 300, 50, 6);
    tileAtlas["commercial"] =
            Tile(this->tileSize, 2, texmng.getRef("commercial"),
                 { staticAnimation, staticAnimation, staticAnimation, staticAnimation},
                 TileType::COMMERCIAL, 300, 50, 4);
    tileAtlas["industrial"] =
            Tile(this->tileSize, 2, texmng.getRef("industrial"),
                 { staticAnimation, staticAnimation, staticAnimation,
                   staticAnimation },
                 TileType::INDUSTRIAL, 300, 50, 4);
    tileAtlas["road"] =
            Tile(this->tileSize, 1, texmng.getRef("road"),
                 { staticAnimation, staticAnimation, staticAnimation,
                   staticAnimation, staticAnimation, staticAnimation,
                   staticAnimation, staticAnimation, staticAnimation,
                   staticAnimation, staticAnimation },
                 TileType::ROAD, 100, 0, 1);
}

void Game::loadStyles() {
    this->stylesheets["button"] = GuiStyle(&this->fonts.at("main_font"), 1,
                                           sf::Color(0xc6,0xc6,0xc6), sf::Color(0x94,0x94,0x94), sf::Color(0x00,0x00,0x00),
                                           sf::Color(0x61,0x61,0x61), sf::Color(0x94,0x94,0x94), sf::Color(0x00,0x00,0x00));
    this->stylesheets["text"] = GuiStyle(&this->fonts.at("main_font"), 0,
                                         sf::Color(0x00,0x00,0x00,0x00), sf::Color(0x00,0x00,0x00), sf::Color(0xff,0xff,0xff),
                                         sf::Color(0x00,0x00,0x00,0x00), sf::Color(0x00,0x00,0x00), sf::Color(0xff,0x00,0x00));

}

void Game::loadFonts() {
    sf::Font font;
    font.loadFromFile("./media/Roboto-Light.ttf");
    this->fonts["main_font"] = font;
}