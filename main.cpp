#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

bool welcomeScreen() {
    sf::RenderWindow window(sf::VideoMode(800, 800), "Welcome Window");
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
    topText.setString("Welcome to Minesweeper");
    topText.setFillColor(sf::Color::Black);
    topText.setCharacterSize(30);
    topText.setPosition(200,25);

    enterName.setFont(font);
    enterName.setString("Enter Your Name:");
    enterName.setFillColor(sf::Color::Black);
    enterName.setCharacterSize(30);
    enterName.setPosition(250,75);

    nameText.setFont(font);
    nameText.setString(name);
    nameText.setFillColor(sf::Color::Black);
    nameText.setCharacterSize(30);
    nameText.setPosition(300,300);

    pressEnter.setFont(font);
    pressEnter.setString("Press Enter to Continue");
    pressEnter.setFillColor(sf::Color::Black);
    pressEnter.setCharacterSize(30);
    pressEnter.setPosition(200,500);

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
                    name += c;
                }
                nameText.setString(name);
            }
        }//end inner while

        window.clear(sf::Color::White);
        window.draw(topText);
        window.draw(enterName);
        window.draw(nameText);
        window.draw(pressEnter);
        window.display();
    } // end while
}

void gameScreen() {
    sf::RenderWindow window(sf::VideoMode(800, 800), "Game Window");

    sf::Font font;
    if (!font.loadFromFile("../files/font.ttf")) {
        return;
    }
    sf::Text topText;

    topText.setFont(font);
    topText.setString("Game Window");
    topText.setFillColor(sf::Color::Black);
    topText.setCharacterSize(30);
    topText.setPosition(200,25);

    while(window.isOpen()) {
        sf::Event event;
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                window.close();
            }
        }//end inner while

        window.clear(sf::Color::White);
        window.draw(topText);
        window.display();
    } // end while

}


int main() {
    if (welcomeScreen())
    {
        gameScreen();
    }

    return 0;
}

// TIP See CLion help at <a
// href="https://www.jetbrains.com/help/clion/">jetbrains.com/help/clion/</a>.
//  Also, you can try interactive lessons for CLion by selecting
//  'Help | Learn IDE Features' from the main menu.