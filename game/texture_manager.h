//
// Created by Dillon Yao on 2/27/17.
//

#ifndef CITYBUILD_TEXTURE_MANAGER_H
#define CITYBUILD_TEXTURE_MANAGER_H


#include <SFML/Graphics/Texture.hpp>
#include <map>

class TextureManager {
private:
    std::map<std::string, sf::Texture> textures;

public:
    void loadTexture(const std::string& name, const std::string &filename);
    sf::Texture& getRef(const std::string& texture);
    TextureManager() {}
};


#endif //CITYBUILD_TEXTURE_MANAGER_H
