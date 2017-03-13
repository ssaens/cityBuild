//
// Created by Dillon Yao on 2/27/17.
//

#ifndef CITYBUILD_MAP_H
#define CITYBUILD_MAP_H


#include <SFML/Graphics.hpp>
#include <string>
#include <map>
#include <vector>
#include "tile.h"

class Map {
private:
    void dfs(std::vector<TileType> &whitelist, sf::Vector2i pos, unsigned int label, unsigned int type);

public:
    unsigned int width, height;

    std::vector<Tile> tiles;

    std::vector<int> resources;

    unsigned int tileSize;
    unsigned int numRegions[1];

    void load(const std::string &filename, unsigned int width, unsigned int height, std::map<std::string, Tile> &tileAtlas);
    void save(const std::string &filename);

    void draw(sf::RenderWindow &window, float dt);

    void findConnectedRegions(std::vector<TileType> &whitelist, unsigned int type);

    void updateDirection(TileType type);

    Map() : tileSize(0), width(0), height(0), numSelected(0) {
        this->numRegions[0] = 1;
    }

    Map(const std::string &filename, unsigned int width, unsigned int height, std::map<std::string, Tile> &tileAtlas) :
            tileSize(8), numSelected(0) {
        load(filename, width, height, tileAtlas);
    }

    /* 0 = Deselected, 1 = Selected, 2 = Invalid */
    std::vector<char> selected;
    unsigned int numSelected;

    /* Select the tiles within the bounds */
    void select(sf::Vector2i start, sf::Vector2i end, std::vector<TileType> blacklist);

    /* Deselect all tiles */
    void clearSelected();
};


#endif //CITYBUILD_MAP_H
