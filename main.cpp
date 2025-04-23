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
    sf::RenderWindow window(sf::VideoMode(width, height), "Game Window");
    Board board(rows, columns, mines);

    while(window.isOpen()) {
        sf::Event event;
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                window.close();
            }
        }//end inner while
        window.clear(sf::Color::White);
        board.drawBoard(window);
        window.display();
    } // end while

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

    return 0;
}

// TIP See CLion help at <a
// href="https://www.jetbrains.com/help/clion/">jetbrains.com/help/clion/</a>.
//  Also, you can try interactive lessons for CLion by selecting
//  'Help | Learn IDE Features' from the main menu.