//
// Created by Joseph on 4/22/2025.
//
#pragma once
#include <string>
#include <unordered_map>
#include <SFML/Graphics.hpp>
using namespace std;

#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H
struct TextureManager {
    unordered_map<string, sf::Texture> textures;
    TextureManager() {
        sf::Texture debugTexture;
        debugTexture.loadFromFile("../files/images/debug.png");
        textures.emplace("debug", debugTexture);

        sf::Texture digitsTexture;
        digitsTexture.loadFromFile("../files/images/digits.png");
        textures.emplace("digits", digitsTexture);

        sf::Texture face_happyTexture;
        face_happyTexture.loadFromFile("../files/images/face_happy.png");
        textures.emplace("face_happy", face_happyTexture);

        sf::Texture face_loseTexture;
        face_loseTexture.loadFromFile("../files/images/face_lose.png");
        textures.emplace("face_lose", face_loseTexture);

        sf::Texture face_winTexture;
        face_winTexture.loadFromFile("../files/images/face_win.png");
        textures.emplace("face_win", face_winTexture);

        sf::Texture flagTexture;
        flagTexture.loadFromFile("../files/images/flag.png");
        textures.emplace("flag", flagTexture);

        sf::Texture leaderboardTexture;
        leaderboardTexture.loadFromFile("../files/images/leaderboard.png");
        textures.emplace("leaderboard", leaderboardTexture);

        sf::Texture mineTexture;
        mineTexture.loadFromFile("../files/images/mine.png");
        textures.emplace("mine", mineTexture);

        sf::Texture number1Texture;
        number1Texture.loadFromFile("../files/images/number_1.png");
        textures.emplace("number1", number1Texture);

        sf::Texture number2Texture;
        number2Texture.loadFromFile("../files/images/number_2.png");
        textures.emplace("number2", number2Texture);

        sf::Texture number3Texture;
        number3Texture.loadFromFile("../files/images/number_3.png");
        textures.emplace("number3", number3Texture);

        sf::Texture number4Texture;
        number4Texture.loadFromFile("../files/images/number_4.png");
        textures.emplace("number4", number4Texture);

        sf::Texture number5Texture;
        number5Texture.loadFromFile("../files/images/number_5.png");
        textures.emplace("number5", number5Texture);

        sf::Texture number6Texture;
        number6Texture.loadFromFile("../files/images/number_6.png");
        textures.emplace("number6", number6Texture);

        sf::Texture number7Texture;
        number7Texture.loadFromFile("../files/images/number_7.png");
        textures.emplace("number7", number7Texture);

        sf::Texture number8Texture;
        number8Texture.loadFromFile("../files/images/number_8.png");
        textures.emplace("number8", number8Texture);

        sf::Texture pauseTexture;
        pauseTexture.loadFromFile("../files/images/pause.png");
        textures.emplace("pause", pauseTexture);

        sf::Texture playTexture;
        playTexture.loadFromFile("../files/images/play.png");
        textures.emplace("play", playTexture);

        sf::Texture tileHiddenTexture;
        tileHiddenTexture.loadFromFile("../files/images/tile_hidden.png");
        textures.emplace("tile_hidden", tileHiddenTexture);

        sf::Texture tileRevealedTexture;
        tileRevealedTexture.loadFromFile("../files/images/tile_revealed.png");
        textures.emplace("tile_revealed", tileRevealedTexture);

    }
};
#endif //TEXTUREMANAGER_H
