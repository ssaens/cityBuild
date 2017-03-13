//
// Created by Dillon Yao on 2/27/17.
//

#ifndef CITYBUILD_TILE_H
#define CITYBUILD_TILE_H


#include <SFML/Graphics.hpp>
#include <vector>
#include "../game/animation.h"

enum class TileType {
    VOID,
    GRASS,
    FOREST,
    WATER,
    RESIDENTIAL,
    COMMERCIAL,
    INDUSTRIAL,
    ROAD,
};

std::string tileTypeToStr(TileType type);

class Tile {
public:

    AnimationHandler animationHandler;
    sf::Sprite sprite;

    TileType type;
    unsigned int tileVariant;

    unsigned int regions[1];

    unsigned int cost;

    double population;

    unsigned int maxPopPerLevel;

    unsigned int maxLevels;

    float production;

    float storedGoods;

    Tile() {}
    Tile(const unsigned int tileSize, const unsigned int height, sf::Texture &texture,
         const std::vector<Animation> &animations,
         const TileType type,
         const unsigned int cost,
         const unsigned int maxPopPerLevel,
         const unsigned int maxLevels) {
        this->type = type;
        this->tileVariant = 0;
        this->regions[0] = 0;

        this->cost = cost;
        this->population = 0;
        this->maxPopPerLevel = maxPopPerLevel;
        this->maxLevels = maxLevels;
        this->production = 0;
        this->storedGoods = 0;

        this->sprite.setOrigin(sf::Vector2f(0.0f, tileSize * (height - 1)));
        this->sprite.setTexture(texture);
        this->animationHandler.frameSize = sf::IntRect(0, 0, tileSize * 2, tileSize * height);
        for (auto animation : animations) {
            this->animationHandler.addAnimation(animation);
        }
        this->animationHandler.update(0.0f);
    }

    void draw(sf::RenderWindow &window, float dt);

    void update();

    std::string getCost() {
        return std::to_string(this->cost);
    }
};


#endif //CITYBUILD_TILE_H
