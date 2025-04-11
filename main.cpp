#include <iostream>
#include <SFML/Graphics.hpp>

void welcomeScreen() {
    sf::RenderWindow window(sf::VideoMode(1200, 1200), "Welcome Window!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Red);

    while(window.isOpen()) {
        sf::Event event;
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear(sf::Color::White);
        window.draw(shape);
        window.display();
    }
}


int main() {
    welcomeScreen();
    // sf::RenderWindow window(sf::VideoMode(1200, 1200), "Welcome Window!");
    // sf::CircleShape shape(100.f);
    // shape.setFillColor(sf::Color::Red);
    //
    // while(window.isOpen()) {
    //     sf::Event event;
    //     while(window.pollEvent(event)) {
    //         if(event.type == sf::Event::Closed) {
    //             window.close();
    //         }
    //     }
    //
    //     window.clear();
    //     window.draw(shape);
    //     window.display();
    // }
    return 0;
}

// TIP See CLion help at <a
// href="https://www.jetbrains.com/help/clion/">jetbrains.com/help/clion/</a>.
//  Also, you can try interactive lessons for CLion by selecting
//  'Help | Learn IDE Features' from the main menu.