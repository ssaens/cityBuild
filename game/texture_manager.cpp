//
// Created by Dillon Yao on 2/27/17.
//

#include <iostream>
#include "texture_manager.h"

void TextureManager::loadTexture(const std::string &name, const std::string &filename) {
    sf::Texture tex;
    if (!tex.loadFromFile(filename)) {
        std::cout << "Failed to load file: " + filename + "\n" << std::endl;
    }
    this->textures[name] = tex;
}

sf::Texture& TextureManager::getRef(const std::string &texture) {
    return this->textures.at(texture);
}