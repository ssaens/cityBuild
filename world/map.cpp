//
// Created by Dillon Yao on 2/27/17.
//

#include "map.h"
#include <fstream>

void Map::load(const std::string &filename, unsigned int width, unsigned int height,
               std::map<std::string, Tile> &tileAtlas) {
    std::ifstream inputFile;
    inputFile.open(filename, std::ios::in | std::ios::binary);

    this->width = width;
    this->height = height;

    for (int pos = 0; pos < this->width * this->height; ++pos) {
        this->resources.push_back(255);
        this->selected.push_back(0);

        TileType tileType;
        inputFile.read((char*)&tileType, sizeof(int));
        switch(tileType)
        {
            default:
            case TileType::VOID:
            case TileType::GRASS:
                this->tiles.push_back((Tile &) tileAtlas.at("grass"));
                break;
            case TileType::FOREST:
                this->tiles.push_back((Tile &) tileAtlas.at("forest"));
                break;
            case TileType::WATER:
                this->tiles.push_back((Tile &) tileAtlas.at("water"));
                break;
            case TileType::RESIDENTIAL:
                this->tiles.push_back((Tile &) tileAtlas.at("residential"));
                break;
            case TileType::COMMERCIAL:
                this->tiles.push_back((Tile &) tileAtlas.at("commercial"));
                break;
            case TileType::INDUSTRIAL:
                this->tiles.push_back((Tile &) tileAtlas.at("industrial"));
                break;
            case TileType::ROAD:
                this->tiles.push_back((Tile &) tileAtlas.at("road"));
                break;
        }
        Tile &tile = this->tiles.back();
        inputFile.read((char *)&tile.tileVariant, sizeof(int));
        inputFile.read((char *)&tile.regions, sizeof(int)*1);
        inputFile.read((char *)&tile.population, sizeof(double));
        inputFile.read((char *)&tile.storedGoods, sizeof(float));
    }
    inputFile.close();
}

void Map::save(const std::string &filename) {
    std::ofstream outputFile;
    outputFile.open(filename, std::ios::out | std::ios::binary);

    for (auto tile : this->tiles) {
        outputFile.write((char *)&tile.type, sizeof(int));
        outputFile.write((char *)&tile.tileVariant, sizeof(int));
        outputFile.write((char *)&tile.regions, sizeof(int)*1);
        outputFile.write((char *)&tile.population, sizeof(double));
        outputFile.write((char *)&tile.storedGoods, sizeof(float));
    }

    outputFile.close();
}

void Map::draw(sf::RenderWindow &window, float dt) {
    for (int y = 0; y < this->height; ++y) {
        for (int x = 0; x < this->width; ++x) {
            sf::Vector2f pos;
            pos.x = (x - y) * this->tileSize + this->width * this->tileSize;
            pos.y = (x + y) * this->tileSize * 0.5f;
            this->tiles[y * this->width + x].sprite.setPosition(pos);

            if (this->selected[y * this->width + x] == 1) {
                this->tiles[y*this->width+x].sprite.setColor(sf::Color(0x7d, 0x7d, 0x7d));
            } else {
                this->tiles[y*this->width+x].sprite.setColor(sf::Color(0xff, 0xff, 0xff));
            }
            this->tiles[y * this->width + x].draw(window, dt);
        }
    }
}

void Map::updateDirection(TileType tileType) {
    for(int y = 0; y < this->height; ++y)
    {
        for(int x = 0; x < this->width; ++x)
        {

            int pos = y * this->width + x;

            bool adjacentTiles[3][3] = {{0,0,0},{0,0,0},{0,0,0}};

            /* Check for adjacent tiles of the same type */
            if(x > 0 && y > 0)
                adjacentTiles[0][0] = (this->tiles[(y-1)*this->width+(x-1)].type == tileType);
            if(y > 0)
                adjacentTiles[0][1] = (this->tiles[(y-1)*this->width+(x  )].type == tileType);
            if(x < this->width-1 && y > 0)
                adjacentTiles[0][2] = (this->tiles[(y-1)*this->width+(x+1)].type == tileType);
            if(x > 0)
                adjacentTiles[1][0] = (this->tiles[(y  )*this->width+(x-1)].type == tileType);
            if(x < width-1)
                adjacentTiles[1][2] = (this->tiles[(y  )*this->width+(x+1)].type == tileType);
            if(x > 0 && y < this->height-1)
                adjacentTiles[2][0] = (this->tiles[(y+1)*this->width+(x-1)].type == tileType);
            if(y < this->height-1)
                adjacentTiles[2][1] = (this->tiles[(y+1)*this->width+(x  )].type == tileType);
            if(x < this->width-1 && y < this->height-1)
                adjacentTiles[2][2] = (this->tiles[(y+1)*this->width+(x+1)].type == tileType);

            /* Change the tile variant depending on the tile position */
            if(adjacentTiles[1][0] && adjacentTiles[1][2] && adjacentTiles[0][1] && adjacentTiles[2][1])
                this->tiles[pos].tileVariant = 2;
            else if(adjacentTiles[1][0] && adjacentTiles[1][2] && adjacentTiles[0][1])
                this->tiles[pos].tileVariant = 7;
            else if(adjacentTiles[1][0] && adjacentTiles[1][2] && adjacentTiles[2][1])
                this->tiles[pos].tileVariant = 8;
            else if(adjacentTiles[0][1] && adjacentTiles[2][1] && adjacentTiles[1][0])
                this->tiles[pos].tileVariant = 9;
            else if(adjacentTiles[0][1] && adjacentTiles[2][1] && adjacentTiles[1][2])
                this->tiles[pos].tileVariant = 10;
            else if(adjacentTiles[1][0] && adjacentTiles[1][2])
                this->tiles[pos].tileVariant = 0;
            else if(adjacentTiles[0][1] && adjacentTiles[2][1])
                this->tiles[pos].tileVariant = 1;
            else if(adjacentTiles[2][1] && adjacentTiles[1][0])
                this->tiles[pos].tileVariant = 3;
            else if(adjacentTiles[0][1] && adjacentTiles[1][2])
                this->tiles[pos].tileVariant = 4;
            else if(adjacentTiles[1][0] && adjacentTiles[0][1])
                this->tiles[pos].tileVariant = 5;
            else if(adjacentTiles[2][1] && adjacentTiles[1][2])
                this->tiles[pos].tileVariant = 6;
            else if(adjacentTiles[1][0])
                this->tiles[pos].tileVariant = 0;
            else if(adjacentTiles[1][2])
                this->tiles[pos].tileVariant = 0;
            else if(adjacentTiles[0][1])
                this->tiles[pos].tileVariant = 1;
            else if(adjacentTiles[2][1])
                this->tiles[pos].tileVariant = 1;
        }
    }
}

void Map::dfs(std::vector<TileType> &whitelist, sf::Vector2i pos, unsigned int label, unsigned int type=0) {
    if (pos.x < 0 || pos.x >= this->width) return;
    if (pos.y < 0 || pos.y >= this->height) return;

    int index = pos.y * this->width + pos.x;

    if (this->tiles[index].regions[type] != 0) return;
    bool found = false;
    for (auto tileType : whitelist) {
        if (tileType == this->tiles[index].type) {
            found = true;
            break;
        }
    }
    if (!found) return;

    this->tiles[index].regions[type] = label;

    dfs(whitelist, pos + sf::Vector2i(-1,  0), label, type);
    dfs(whitelist, pos + sf::Vector2i(0 ,  1), label, type);
    dfs(whitelist, pos + sf::Vector2i(1 ,  0), label, type);
    dfs(whitelist, pos + sf::Vector2i(0 , -1), label, type);
}

void Map::findConnectedRegions(std::vector<TileType> &whitelist, unsigned int type) {
    unsigned int regions = 1;
    for (auto &tile : this->tiles) tile.regions[type] = 0;

    for (int y = 0; y < this->height; ++y) {
        for (int x = 0; x < this->width; ++x) {
            int index = y * this->width + x;
            bool found = false;
            for (auto tileType : whitelist) {
                if (tileType == this->tiles[index].type) {
                    found = true;
                    break;
                }
            }
            if (this->tiles[index].regions[type] == 0 && found) {
                dfs(whitelist, sf::Vector2i(x, y), regions++, type);
            }
        }
    }
    this->numRegions[type] = regions;
}

void Map::select(sf::Vector2i start, sf::Vector2i end, std::vector<TileType> blacklist) {
    if (end.x < start.x) std::swap(start.x, end.x);
    if (end.y < start.y) std::swap(start.y, end.y);

    if (end.x >= this->width)       end.x = this->width - 1;
    else if (end.x < 0)             end.x = 0;
    if (end.y >= this->height)      end.y = this->height - 1;
    else if (end.y < 0)             end.y = 0;
    if (start.x >= this->width)     start.x = this->width - 1;
    else if (start.x < 0)           start.x = 0;
    if (start.y >= this->height)    start.y = this->height - 1;
    else if (start.y < 0)           start.y = 0;

    for (int y = start.y; y < end.y; ++y) {
        for (int x = start.x; x < end.x; ++x) {
            unsigned int index = y * this->width + x;
            this->selected[index] = 1;
            ++this->numSelected;
            for (auto type : blacklist)
            {
                if (this->tiles[index].type == type)
                {
                    this->selected[index] = 2;
                    --this->numSelected;
                    break;
                }
            }
        }
    }
}

void Map::clearSelected() {
    for (int i = 0; i < this->selected.size(); ++i) {
        this->selected[i] = 0;
    }
    this->numSelected = 0;
}