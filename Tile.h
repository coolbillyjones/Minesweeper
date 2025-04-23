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
    sf::Sprite overlay;
    std::vector<Tile*> adjacent_tiles;
    Tile(TextureManager& texturesMap) {
        flagged = false;
        revealed = false;
        sprite.setTexture(texturesMap.textures["tile_hidden"]);
    }

    void revealTile(TextureManager& texturesMap)
    {
        revealed = true;
        sprite.setTexture(texturesMap.textures["tile_revealed"]);
        if (flagged)
        {
            overlay.setTexture(texturesMap.textures["flag"]);
        } else if (mine)
        {
            overlay.setTexture(texturesMap.textures["mine"]);
        }

    }

    void resetTile(TextureManager& texturesMap)
    {
        flagged = false;
        revealed = false;
        mine = false;
        sprite.setTexture(texturesMap.textures["tile_hidden"]);
        overlay.setTexture(texturesMap.textures["tile_hidden"]);
    }

    void findAdjacentMines()
    {
        for (int i = 0; i < adjacent_tiles.size(); i++)
        {
            if (adjacent_tiles[i]->mine)
            {
                adjacent_mines++;
            }
        }
    }
};



#endif //TILE_H
