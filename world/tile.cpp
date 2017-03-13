//
// Created by Dillon Yao on 2/27/17.
//

#include "tile.h"

void Tile::draw(sf::RenderWindow &window, float dt) {
    this->animationHandler.changeAnimation(this->tileVariant);
    this->animationHandler.update(dt);
    this->sprite.setTextureRect(this->animationHandler.bounds);
    window.draw(this->sprite);
}

void Tile::update() {
    if ((this->type == TileType::RESIDENTIAL ||
            this->type == TileType::COMMERCIAL ||
            this->type == TileType::INDUSTRIAL) &&
            (this->population >= this->maxPopPerLevel * this->tileVariant + 1) &&
            this->tileVariant < this->maxLevels){
        if (rand() % int(1e4) < 1e2 / (this->tileVariant + 1)) this->tileVariant++;
    }
}

std::string tileTypeToStr(TileType type) {
    switch(type) {
        default:
        case TileType::VOID:            return "Void";
        case TileType::GRASS:           return "Grass";
        case TileType::FOREST:          return "Forest";
        case TileType::WATER:           return "Water";
        case TileType::RESIDENTIAL:     return "Residential zone";
        case TileType::COMMERCIAL:      return "Commercial zone";
        case TileType::INDUSTRIAL:      return "Industrial zone";
        case TileType::ROAD:            return "Road";
    }
}
