//
// Created by Joseph on 4/22/2025.
//
#include <vector>
#include <random>
#include "Tile.H"
#ifndef BOARD_H
#define BOARD_H



struct Board {
    int columns, rows, mines, count, numRevealed;
    bool win = false;
    TextureManager textureMap;
    sf::Vector2u tileSize;
    std::vector<std::vector<Tile*>> tiles;

    Board(int rows, int columns, int mines)
    {
        this->columns = columns;
        this->rows = rows;
        this->mines = mines;
        count = mines;
        numRevealed = 0;
        tileSize = textureMap.textures["tile_hidden"].getSize();
        tiles.resize(rows, std::vector<Tile*>(columns, nullptr));
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < columns; j++)
            {
                tiles[i][j] = new Tile(textureMap);
                tiles[i][j]->sprite.setPosition(j * tileSize.x, i * tileSize.y);
                tiles[i][j]->overlay.setPosition(j * tileSize.x, i * tileSize.y);
            }
        }
        assignMines();
        findAdjacents();
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

    void resetBoard()
    {
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < columns; j++)
            {
                tiles[i][j]->resetTile(textureMap);
            }
        }
        count = mines;
        numRevealed = 0;
        win = false;
        assignMines();
        findAdjacents();
    }
    void drawBoard(sf::RenderWindow& window) {
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < columns; j++)
            {
                window.draw(tiles[i][j]->sprite);
                if (tiles[i][j]->revealed)
                {
                    window.draw(tiles[i][j]->overlay);
                }
            }
        }
    }

    void assignMines()
    {
        std::vector<std::pair<int, int>> coords;
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < columns; j++)
            {
                coords.push_back(make_pair(i,j));
            }
        }

        std::random_shuffle(coords.begin(), coords.end());
        for (int k = 0; k < mines; k++)
        {
            auto [x, y] = coords[k];
            tiles[x][y]->mine = true;
            tiles[x][y]->overlay.setTexture(textureMap.textures["mine"]);
        }
    }

    void revealAllMines()
    {
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < columns; j++)
            {
                if (tiles[i][j]->mine)
                {
                    tiles[i][j]->revealTile(textureMap, numRevealed);
                }
            }
        }
    }

    void assignReveal(bool pause)
    {
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < columns; j++)
            {
                if (pause)
                {
                    tiles[i][j]->overlay.setTexture(textureMap.textures["tile_revealed"]);
                } else
                {
                    tiles[i][j]->overlay.setTexture(textureMap.textures["tile_hidden"]);
                }
            }
        }
    }

    void flagRemaining()
    {
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < columns; j++)
            {
                if (!tiles[i][j]->revealed)
                {
                    tiles[i][j]->flagged = true;
                    tiles[i][j]->revealTile(textureMap, numRevealed);
                }
            }
        }
    }

    void findAdjacents()
    {
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < columns; j++)
            {
                Tile* tile = tiles[i][j];
                for (int k = -1; k <= 1; k++)
                {
                    for (int l = -1; l <= 1; l++)
                    {
                        if (k == 0 && l == 0)
                        {
                            continue;
                        }

                        int newR = i + k;
                        int newC = j + l;
                        if ((newR >= 0 && newR < rows) && (newC >= 0 && newC < columns))
                        {
                            tile->adjacent_tiles.push_back(tiles[newR][newC]);
                            if (tiles[newR][newC]->mine) {
                                tile->adjacent_mines += 1;
                            }
                        }
                    }
                }
            }
        }
    }

};





#endif //BOARD_H
