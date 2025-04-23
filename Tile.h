//
// Created by Joseph on 4/22/2025.
//
#include <vector>
#include "TextureManager.h"
#ifndef TILE_H
#define TILE_H



struct Tile {
    bool mine;
    bool flagged;
    bool revealed;
    int adjacent_mines;
    sf::Sprite sprite;
    std::vector<Tile*> adjacent_tiles;
    Tile(TextureManager& texturesMap) {
        flagged = false;
        revealed = false;
        sprite.setTexture(texturesMap.textures["tile_hidden"]);
    }

    void updateTile()
    {

    }

    void resetTile(TextureManager texturesMap)
    {
        flagged = false;
        revealed = false;
        sf::Sprite sprite(texturesMap.textures["tile_hidden"]);
    }

};



#endif //TILE_H
