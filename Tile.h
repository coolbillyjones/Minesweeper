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
        mine = false;
        revealed = false;
        adjacent_mines = 0;
        sprite.setTexture(texturesMap.textures["tile_hidden"]);
    }

    void revealTile(TextureManager& texturesMap, int& numRevealed)
    {
        revealed = true;
        sprite.setTexture(texturesMap.textures["tile_revealed"]);
        if (flagged)
        {
            overlay.setTexture(texturesMap.textures["flag"]);
        } else if (mine)
        {
            overlay.setTexture(texturesMap.textures["mine"]);
        } else
        {
            numRevealed += 1;
            if (adjacent_mines > 0)
            {
                std::string adjacent_mines_str = "number" + std::to_string(adjacent_mines);
                overlay.setTexture(texturesMap.textures[adjacent_mines_str]);
            } else
            {
                overlay.setTexture(texturesMap.textures["tile_revealed"]);
            }
        }


    }

    void resetTile(TextureManager& texturesMap)
    {
        flagged = false;
        revealed = false;
        mine = false;
        adjacent_mines = 0;
        sprite.setTexture(texturesMap.textures["tile_hidden"]);
        overlay.setTexture(texturesMap.textures["tile_hidden"]);
    }

    void revealAdjacents(TextureManager& texturesmap, int& numRevealed)
    {
        for (Tile* tile : adjacent_tiles)
        {
            if (tile->mine)
            {
                continue;
            }
            if (tile->revealed)
            {
                continue;
            }
            if (tile->adjacent_mines > 0)
            {
                tile->revealed = true;
                tile->revealTile(texturesmap, numRevealed);
                continue;
            }
            tile->revealed = true;
            tile->revealTile(texturesmap, numRevealed);
            tile->revealAdjacents(texturesmap, numRevealed);

        }
    }
};



#endif //TILE_H
