//
// Created by Joseph on 4/22/2025.
//
#include <vector>
#include "Tile.H"
#ifndef BOARD_H
#define BOARD_H



struct Board {
    int columns, rows, mines;
    TextureManager textureMap;
    sf::Vector2u tileSize;
    std::vector<std::vector<Tile*>> tiles;

    Board(int rows, int columns, int mines)
    {
        this->columns = columns;
        this->rows = rows;
        this->mines = mines;
        tileSize = textureMap.textures["tile_hidden"].getSize();
        tiles.resize(rows, std::vector<Tile*>(columns, nullptr));
    }

    ~Board()
    {
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < columns; j++)
            {
                delete tiles[i][j];
            }
        }
    }
    void drawBoard(sf::RenderWindow& window) {
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < columns; j++)
            {
                if (tiles[i][j] == nullptr)
                {
                    tiles[i][j] = new Tile(textureMap);
                    tiles[i][j]->sprite.setPosition(j * tileSize.x, i * tileSize.y);
                }
                window.draw(tiles[i][j]->sprite);
            }
        }
    }
};



#endif //BOARD_H
