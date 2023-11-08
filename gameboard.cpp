#include "GameBoard.h"
#include "tile.h"
#include <fstream>
#include <random>
#include "Tile.h"
#include <utility> // for std::pair
#include "random.cpp"
std::mt19937 Random::random(std::random_device{}());
std::unordered_map<std::string, sf::Texture> GameBoard::textures;
GameBoard::GameBoard(){
    num_mines = 0;
    num_flags = 0;
    num_cols = 0;
    num_rows = 0;
    losted = false;
    woned = false;
    paused = false;
    timerRunning = true;
    leaderboardOn = false;
    tileOpenedSprite.setTexture(GameBoard::getTexture("tile_revealed"));
    tileClosedSprite.setTexture(GameBoard::getTexture("tile_hidden"));
    minesprite.setTexture(GameBoard::getTexture("mine"));
    flagSprite.setTexture(GameBoard::getTexture("flag"));
    num_1.setTexture(GameBoard::getTexture("number_1"));
    num_2.setTexture(GameBoard::getTexture("number_2"));
    num_3.setTexture(GameBoard::getTexture("number_3"));
    num_4.setTexture(GameBoard::getTexture("number_4"));
    num_5.setTexture(GameBoard::getTexture("number_5"));
    num_6.setTexture(GameBoard::getTexture("number_6"));
    num_7.setTexture(GameBoard::getTexture("number_7"));
    num_8.setTexture(GameBoard::getTexture("number_8"));
    sad_face.setTexture(GameBoard::getTexture("face_lose"));
    reg_face.setTexture(GameBoard::getTexture("face_happy"));
    cool_face.setTexture(GameBoard::getTexture("face_win"));
    debug_button.setTexture(GameBoard::getTexture("debug"));
    leaderboard_button.setTexture(GameBoard::getTexture("leaderboard"));
    pause_button.setTexture(GameBoard::getTexture("pause"));
    play_button.setTexture(GameBoard::getTexture("play"));
    digitSprite.setTexture(GameBoard::getTexture("digits"));
}



void GameBoard::loadTexture(std::string fileName) {
    std::string path = "files/images/";
    path += fileName + ".png";
    textures[fileName].loadFromFile(path);
}

sf::Texture& GameBoard::getTexture(std::string textureName) {
    if (textures.find(textureName) == textures.end())
        loadTexture(textureName);
    return textures[textureName];
}

int GameBoard::getNumRows() const {
    return num_rows;
}

int GameBoard::getNumCols() const {
    return num_cols;
}

int GameBoard::getNumMines() const {
    return num_mines;
}

int GameBoard::getNumTiles() const {
    return num_tiles;
}

void GameBoard::display(const std::string& path) {
    std::cout << "display";
    std::fstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + path);
    }
    std::cout << "fileopened";
    file >> num_cols >> num_rows  >> num_mines;
    for ( int i = 0; i < (num_cols * num_rows); i++) {
        Tile t;
        tiles.push_back(t);

    }
    int counter = 0;
    while (counter < num_mines) {
        int randomIndex =  Random::Int(0, (num_rows*num_cols)-1);;
        if (!tiles[randomIndex].getMineStat()) {
            tiles[randomIndex].setsState(true);
            counter++;
        }
    }
    std::cout << "states gotten";
    for (int i = 0; i < tiles.size(); i++) {
        tiles[i].minesadjacent(tiles, i, num_cols, num_cols*num_rows);
        tiles.at(i).findadjoverall(tiles, i, num_cols, num_cols*num_rows);
    }
    std::cout << "adjacents";

}

void GameBoard::Draw(sf::RenderWindow& window) {
    //draw out each tile in this function
    int k = 0;
    for (int i = 0; i < num_rows; i++) {
        for (int j = 0; j < num_cols; j++) {
            tiles.at(k).setpos(j * 32, i * 32);
            tiles.at(k).Draw(window);
            k++;
        }
    }

    // draw the bar at bottom
    sf::RectangleShape bottombar(sf::Vector2f(getNumCols() * 32, 90.0f));
    bottombar.setFillColor(sf::Color::White);
    bottombar.setPosition(0, getNumRows() * 32);
    window.draw(bottombar);
    // draw little smileys all around
    sad_face.setPosition((((num_cols) / 2.0) * 32)-32, 32 *((num_rows)+0.5f));
    reg_face.setPosition((((num_cols) / 2.0) * 32)-32, 32 *((num_rows)+0.5f));
    cool_face.setPosition((((num_cols) / 2.0) * 32)-32, 32 *((num_rows)+0.5f));
    if (losted){
        window.draw(sad_face);
    }else if (woned) {
        window.draw(cool_face);
    }else {
        window.draw(reg_face);
    }
    debug_button.setPosition(((num_cols) * 32) - 304, 32 * ((num_rows)+0.5f));
    window.draw(debug_button);
    leaderboard_button.setPosition(((num_cols) * 32) - 176, 32 * ((num_rows)+0.5f));
    window.draw(leaderboard_button);
    if (paused){
        play_button.setPosition(((num_cols) * 32) - 240, 32 * ((num_rows)+0.5f));
        window.draw(play_button);
    }
    else{
        pause_button.setPosition(((num_cols) * 32) - 240, 32 * ((num_rows)+0.5f));
        window.draw(pause_button);
    }

    int countyaf = num_mines-num_flags;
    if (countyaf < 0) {
        digitSprite.setTextureRect(sf::IntRect(210, 0, 21, 32));
        digitSprite.setPosition(0, 32 * ((num_rows)+0.5f)+16);
        window.draw(digitSprite);
    }
    countyaf = abs(countyaf);
    int firstnum = (int) countyaf / 100;
    digitSprite.setTextureRect(sf::IntRect(21 * firstnum, 0, 21, 32));
    digitSprite.setPosition(12, 32 * ((num_rows)+0.5f)+16);
    window.draw(digitSprite);
    int secondnum = (int) (countyaf % 100) / 10;
    digitSprite.setTextureRect(sf::IntRect(21 * secondnum, 0, 21, 32));
    digitSprite.setPosition(33, 32 *((num_rows)+0.5f)+16);
    window.draw(digitSprite);
    int thirdnum = (int) countyaf % 10;
    digitSprite.setTextureRect(sf::IntRect(21 * thirdnum, 0, 21, 32));
    digitSprite.setPosition(54, 32 *((num_rows)+0.5f)+16);
    window.draw(digitSprite);
}



void GameBoard::lefty(int x, int y, sf::Event event, sf::RenderWindow& window){
    std::cout << "clicked work";
    if (event.mouseButton.button == sf::Mouse::Left) {
        auto endPoints = tiles.at(0).getShow().getGlobalBounds();
        for (int i = 0; i < tiles.size(); i++) {
            endPoints = tiles.at(i).getShow().getGlobalBounds();
            //reveal tile w no flag
            if (!losted && !woned) {
                if (endPoints.contains(x, y) && !tiles.at(i).getFlagStat()) {
                    std::cout << "this is working" <<std::endl;
                    reveal(&tiles.at(i));
                    tiles.at(i).Draw(window);
                }
            }
            //lost if mine
            if(endPoints.contains(x, y) && tiles.at(i).getMineStat()) {
                losted = true;
                for (int i = 0; i < tiles.size(); i++) {
                    if (tiles.at(i).getMineStat()) {
                        reveal(&tiles.at(i));
                        tiles.at(i).isShown;
                        tiles.at(i).Draw(window);
                    }
                }
            }

        }
        //debug button
        if(!losted && !woned && debug_button.getGlobalBounds().contains(x,y)) {
            for (int i = 0; i < tiles.size(); i++) {
                tiles[i].debugger = !tiles[i].debugger;
                tiles[i].Draw(window);
            }
        }
        if (!losted && !woned && pause_button.getGlobalBounds().contains(x,y) && !paused){
            paused = true;
        }
        else{
            paused = false;
        }
        if (leaderboard_button.getGlobalBounds().contains(x,y)){
            leaderboardOn = true;
        }
        else if (leaderboard_button.getGlobalBounds().contains(x,y)){
            leaderboardOn = false;
        }
        //restart button
        if (reg_face.getGlobalBounds().contains(x,y) || sad_face.getGlobalBounds().contains(x,y) || cool_face.getGlobalBounds().contains(x,y)) {
            losted = false;
            woned = false;
            tiles.clear();
            num_mines = 0;
            num_flags = 0;
            display("files/board_config.cfg");
        }}}



void GameBoard::righty(int x, int y, sf::Event event, sf::RenderWindow& window) {
    auto endPoints = tiles.at(0).getShow().getGlobalBounds();
    for (int i = 0; i < tiles.size(); i++) {
        endPoints = tiles[i].getShow().getGlobalBounds();
        //reveal tile w no flag
        if (!losted && !woned && !tiles[i].isShown) {
            if (endPoints.contains(x, y) && !tiles.at(i).getFlagStat()) {
                std::cout << "flag is placed" << std::endl;
                tiles[i].placeFlag();
                window.draw(flagSprite);
                tiles[i].Draw(window);
                num_flags++;
            } else if (endPoints.contains(x, y) && tiles.at(i).getFlagStat()) {
                std::cout << "byebye flag" << std::endl;
                tiles[i].removeFlag();
                window.draw(tileClosedSprite);
                num_flags--;
            }
        }
    }
}

GameBoard::~GameBoard(){
    tiles.clear();
}

void GameBoard::reveal(Tile* tile) {
    if (!tile->gettileRevealed() && !tile->getFlagStat()) {
        tile->revealTile(true);
        if (tile->getMineStat()) {
            // End the game or mark the tile as a mine hit
        }
        else if (tile->minesAreAdjacent.size() == 0) {
            // If the tile is not a mine and has no adjacent mines, recursively reveal adjacent tiles
            for (int i = 0; i < tile->tilesAreAdjacent.size(); i++) {
                reveal(tile->tilesAreAdjacent.at(i));
            }
        }
    }
}
void GameBoard::checkWin() {
    int numMines = 0;
    int numFlags = 0;
    int numRevealed = 0;
    int numTiles = tiles.size();

    for (Tile tile : tiles) {
        if (tile.getMineStat()) {
            numMines++;
            if (tile.getFlagStat()) {
                numFlags++;
            }
        } else {
            if (tile.gettileRevealed()) {
                numRevealed++;
            }
        }
    }

    if (numFlags == numMines && numRevealed == numTiles - numMines) {
        woned = true;
    }
}







