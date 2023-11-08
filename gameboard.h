#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <ctype.h>
#include "tile.h"
#include <random>
#include <unordered_map>
#include <string>

class GameBoard {
public:
    sf::Vector2f position;
    sf::Sprite minesprite;
    sf::Sprite tileClosedSprite;
    sf::Sprite tileOpenedSprite;
    sf::Sprite flagSprite;
    sf::Sprite num_1;
    sf::Sprite num_2;
    sf::Sprite num_4;
    sf::Sprite num_3;
    sf::Sprite num_5;
    sf::Sprite num_6;
    sf::Sprite num_7;
    sf::Sprite num_8;
    sf::Texture textureopen;
    sf::Sprite sad_face;
    sf::Sprite reg_face;
    sf::Sprite cool_face;
    sf::Sprite debug_button;
    sf::Sprite leaderboard_button;
    sf::Sprite pause_button;
    sf::Sprite play_button;
    sf::Texture digitTexture;
    sf::Sprite digitSprite;
    GameBoard();
    int num_rows;
    int num_cols;
    int num_mines;
    int num_tiles;
    int num_flags;
    static std::unordered_map<std::string, sf::Texture> textures;
    std::string pathoffiles;
    bool woned;
    bool losted;
    bool paused;
    bool leaderboardOn;
    bool timerRunning;
    sf::Sprite leaderboard;
    sf::Sprite debug;
    std::vector<Tile> tiles;
    void display(const std::string& path);
    void Draw(sf::RenderWindow& window);
    void lefty(int x, int y, sf::Event event, sf::RenderWindow& window);
    void righty(int x, int y, sf::Event event, sf::RenderWindow& window);
    void reveal(Tile* tile);
    void checkWin();
    //Tile** tiles;
    ~GameBoard();
    int getNumRows() const;
    int getNumCols() const;
    int getNumMines() const;
    int getNumTiles() const;
    static void loadTexture(std::string fileName);
    static sf::Texture& getTexture(std::string textureName);
};

