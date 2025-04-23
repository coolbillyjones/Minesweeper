#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <SFML/Graphics.hpp>
#include "Board.h"


void setText(sf::Text &text, float x, float y){
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width/2.0f,
        textRect.top + textRect.height/2.0f);
    text.setPosition(sf::Vector2f(x, y));
}

void setCounter(int count, std::vector<sf::Sprite> &sprites, TextureManager& textureMap, int rows)
{
    std::string value;
    if (count < 0)
    {
        value += '-';
        count = -count;
    }
    value += std::to_string(count);

    if (value.length() < 3)
    {
        if (value[0] == '-')
        {
            value.insert(1, "0");
        } else
        {
            while (value.length() < 3)
            {
                value.insert(0, "0");
            }
        }
    }// end making string

    for (int i = 0; i < 3; i++)
    {
        int index = 0;
        if (value[i] == '-')
        {
            index = 10;
        } else
        {
            index = value[i] - '0';
        }

        sprites[i].setTexture(textureMap.textures["digits"]);
        sprites[i].setTextureRect(sf::IntRect(index*21, 0, 21, 32));
        sprites[i].setPosition(33 + i * 21, 32 * (rows + 0.5) + 16);
    }
}


bool welcomeScreen(int columns, int rows) {
    int height = (rows * 32) + 100;
    int width = columns * 32;
    sf::RenderWindow window(sf::VideoMode(width, height), "Welcome Window");
    sf::Font font;
    if (!font.loadFromFile("../files/font.ttf")) {
        return false;
    }

    sf::Text topText;
    sf::Text enterName;
    sf::Text nameText;
    sf::Text pressEnter;
    std::string name;

    topText.setFont(font);
    topText.setString("WELCOME TO MINESWEEPER");
    topText.setStyle(sf::Text::Bold);
    topText.setStyle(sf::Text::Underlined);
    topText.setFillColor(sf::Color::White);
    topText.setCharacterSize(24);
    setText(topText, width / 2, height / 2 - 150);

    enterName.setFont(font);
    enterName.setString("Enter Your Name:");
    enterName.setStyle(sf::Text::Bold);
    enterName.setFillColor(sf::Color::White);
    enterName.setCharacterSize(20);
    setText(enterName, width / 2, height / 2 - 75);

    nameText.setFont(font);
    nameText.setString("|");
    nameText.setFillColor(sf::Color::Yellow);
    nameText.setCharacterSize(18);



    while(window.isOpen()) {
    sf::Event event;
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                return false;
                window.close();
            }
            if(event.type == sf::Event::KeyPressed && !name.empty()) {
                if (event.key.code == sf::Keyboard::Enter) {
                    return true;
                    window.close();
                }
            }
            if (event.type == sf::Event::TextEntered) {
                char c = event.text.unicode;
                if (event.text.unicode == 8 && !name.empty()) {
                    name.pop_back();
                }
                if (((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) && name.length() < 10) {
                    if (name.length() == 0)
                    {
                        name += toupper(c);
                    } else
                    {
                        name += tolower(c);
                    }

                }
                nameText.setString(name + "|" );
            }
        }//end inner while
        setText(nameText, width / 2, height / 2 - 45);

        window.clear(sf::Color::Blue);
        window.draw(topText);
        window.draw(enterName);
        window.draw(nameText);
        window.display();
    } // end while
}

void gameScreen(int columns, int rows, int mines) {
    int height = (rows * 32) + 100;
    int width = columns * 32;
    std::vector<sf::Sprite> counterSprites(3);
    sf::RenderWindow window(sf::VideoMode(width, height), "Game Window");
    Board board(rows, columns, mines);
    setCounter(board.count, counterSprites, board.textureMap, rows);

    sf::Sprite debugButton;
    debugButton.setTexture(board.textureMap.textures["debug"]);
    debugButton.setPosition((columns*32)-304, 32*(rows+0.5));

    sf::Sprite happyFaceButton;
    happyFaceButton.setTexture(board.textureMap.textures["face_happy"]);
    happyFaceButton.setPosition(((columns/2)*32)-32, 32*(rows+0.5));

    sf::Sprite pauseButton;
    pauseButton.setTexture(board.textureMap.textures["pause"]);
    pauseButton.setPosition((columns*32)-240, 32*(rows+0.5));

    sf::Sprite leaderboardButton;
    leaderboardButton.setTexture(board.textureMap.textures["leaderboard"]);
    leaderboardButton.setPosition((columns*32)-176, 32*(rows+0.5));

    sf::Sprite counter;
    counter.setTexture(board.textureMap.textures["digits"]);
    counter.setPosition((columns*32)-16, 32*(rows+0.5));


    while(window.isOpen()) {
        sf::Event event;
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                window.close();
            }
            if (board.numRevealed == rows * columns - mines)
            {
                board.win = true;
                board.flagRemaining();
            }
            if (event.type == sf::Event::MouseButtonPressed)
            {
                int x = event.mouseButton.x;
                int y = event.mouseButton.y;
                if (y < rows * board.tileSize.y)
                {
                    int col = x / board.tileSize.x;
                    int row = y / board.tileSize.y;
                    Tile* clicked = board.tiles[row][col];
                    if (event.mouseButton.button == sf::Mouse::Left)
                    {
                        if (clicked->flagged)
                        {

                        } else if (clicked->mine)
                        {
                            clicked->revealTile(board.textureMap, board.numRevealed);
                            board.revealAllMines();
                            happyFaceButton.setTexture(board.textureMap.textures["face_lose"]);
                        } else
                        {
                            clicked->revealTile(board.textureMap, board.numRevealed);
                            if (clicked->adjacent_mines == 0)
                            {
                                clicked->revealAdjacents(board.textureMap, board.numRevealed);
                            }
                        }

                    } else if (event.mouseButton.button == sf::Mouse::Right)
                    {
                        if (clicked->flagged)
                        {
                            clicked->flagged = false;
                            clicked->overlay.setTexture(board.textureMap.textures["tile_hidden"]);
                            board.count += 1;
                            setCounter(board.count, counterSprites, board.textureMap, rows);
                        } else
                        {
                            clicked->flagged = true;
                            clicked->revealTile(board.textureMap, board.numRevealed);
                            board.count -= 1;
                            setCounter(board.count, counterSprites, board.textureMap, rows);
                        }

                    }

                } else
                {
                    sf::Vector2f mousePos(x, y);
                    if (event.mouseButton.button == sf::Mouse::Left)
                    {
                        if (debugButton.getGlobalBounds().contains(mousePos))
                        {
                            board.revealAllMines();
                        } else if (happyFaceButton.getGlobalBounds().contains(mousePos))
                        {
                            board.resetBoard();
                            happyFaceButton.setTexture(board.textureMap.textures["face_happy"]);
                        }
                    }
                }//end else

            }//mouse Button if
        }//end inner while
        window.clear(sf::Color::White);
        board.drawBoard(window);
        window.draw(debugButton);
        window.draw(happyFaceButton);
        window.draw(pauseButton);
        window.draw(leaderboardButton);
        for (int i = 0; i < 3; i++)
        {
            window.draw(counterSprites[i]);
        }
        window.display();
    } // end while

}

void leaderBoard()
{

}


int main() {
    std::ifstream config("../files/config.cfg");
    if (!config.is_open())
    {
        std::cerr << "Error opening config file" << std::endl;
        return 0;
    }
    int columns, rows, mines;
    config >> columns >> rows >> mines;
    config.close();

    if (welcomeScreen(columns, rows))
    {
        gameScreen(columns, rows, mines);
    }

    leaderBoard();

    return 0;
}

// TIP See CLion help at <a
// href="https://www.jetbrains.com/help/clion/">jetbrains.com/help/clion/</a>.
//  Also, you can try interactive lessons for CLion by selecting
//  'Help | Learn IDE Features' from the main menu.