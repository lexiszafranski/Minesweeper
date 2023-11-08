//
// Created by princ on 4/18/2023.
//
#include <iostream>
#include <SFML/Graphics.hpp>
#include "tile.h"
#include "gameboard.h"

Tile::Tile(){
    hasMine = false;
    hasFlag = false;
    isShown = false;
    debugger = false;
    loser = false;
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
    numbersForBoard.push_back(num_1);
    numbersForBoard.push_back(num_2);
    numbersForBoard.push_back(num_3);
    numbersForBoard.push_back(num_4);
    numbersForBoard.push_back(num_5);
    numbersForBoard.push_back(num_6);
    numbersForBoard.push_back(num_7);
    numbersForBoard.push_back(num_8);
    numbersForBoard.push_back(num_8);
}

bool Tile::getMineStat() {
    return hasMine;
}

bool Tile::gettileRevealed() {
    return isShown;
}

bool Tile::getFlagStat() {
    return hasFlag;
}

void Tile::revealTile(bool tilereveal)  {
    isShown = tilereveal;
}

void Tile::setsState(bool stateofMine) {
    hasMine = stateofMine;
}
void Tile::Draw(sf::RenderWindow &window) {
    if (isShown) {

        window.draw(tileOpenedSprite);
    }
    if(minesAreAdjacent.size() >0){
        window.draw(numbersForBoard.at(minesAreAdjacent.size()-1));
    }
    else{
        window.draw(tileOpenedSprite);
    }
    if (!debugger) {
        if (hasMine) {
            // load mine sprite and draw
            window.draw(minesprite);
        }
        if (!isShown) {
            window.draw(tileClosedSprite);
        }
    } else {
        if (!isShown) {
            window.draw(tileClosedSprite);
        }
        if (hasFlag) {
            window.draw(flagSprite);
        }
        if (hasMine) {
            window.draw(minesprite);
        }
    }
    if (hasFlag && !debugger) {
        sf::Texture flagtexture;
        window.draw(flagSprite);
    }
}

void Tile::setpos(float x, float y) {
    minesprite.setPosition(x,y);
    flagSprite.setPosition(x,y);
    tileClosedSprite.setPosition(x,y);
    tileOpenedSprite.setPosition(x,y);
    for (int q = 0; q < numbersForBoard.size(); q++){
        numbersForBoard.at(q).setPosition(x,y);
    }

}

void Tile::minesadjacent(std::vector<Tile> &tiles, int rows, int columns, int tile_count) {
    if (!getMineStat()){
        if ((rows - 1 >= 0) && (rows - 1 < tile_count) && tiles.at(rows - 1).getMineStat() && (rows % columns != 0)){
            minesAreAdjacent.push_back(&(tiles.at(rows - 1)));
        }
        if ((rows + 1 >= 0) && (rows + 1 < tile_count) && tiles.at(rows + 1).getMineStat() && (rows % columns != (columns - 1))){
            minesAreAdjacent.push_back(&(tiles.at(rows + 1)));
        }
        if ((rows + columns + 1 >= 0) && (rows + columns + 1 < tile_count) &&
            tiles.at(rows + columns + 1).getMineStat() && (rows % columns != (columns - 1))){
            minesAreAdjacent.push_back(&(tiles.at(rows + columns + 1)));
        }
        if ((rows + columns >= 0) && (rows + columns < tile_count) && tiles.at(rows + columns).getMineStat()){
            minesAreAdjacent.push_back(&(tiles.at(rows + columns)));
        }
        if ((rows - columns >= 0) && (rows - columns < tile_count) && tiles.at(rows - columns).getMineStat()){
            minesAreAdjacent.push_back(&(tiles.at(rows - columns)));
        }
        if ((rows + columns - 1 >= 0) && (rows + columns - 1 < tile_count) &&
            tiles.at(rows + columns - 1).getMineStat() && (rows % columns != 0)){
            minesAreAdjacent.push_back(&(tiles.at(rows + columns - 1)));
        }
        if (((rows - columns - 1) >= 0) && ((rows - columns - 1) < tile_count) &&
            tiles.at(rows - columns - 1).getMineStat() && (rows % columns != 0)){
            minesAreAdjacent.push_back(&(tiles.at(rows - columns - 1)));
        }
        if ((rows - columns + 1 >= 0) && (rows - columns < tile_count) && tiles.at(rows - columns + 1).getMineStat() && (rows % columns != (columns - 1))){
            minesAreAdjacent.push_back(&(tiles.at(rows - columns + 1)));
        }
    }
}
void Tile::findadjoverall(std::vector<Tile> &tiles, int row, int col, int tile_count) {
    if (row - 1 >= 0 && row - 1 < tile_count && row % col !=0) {
        tilesAreAdjacent.push_back(&tiles[row - 1]);
    }
    if (row + 1 >= 0 && row + 1 < tile_count && row % col != (col - 1)) {
        tilesAreAdjacent.push_back(&(tiles[row + 1]));
    }
    if (row + col + 1 >= 0 && row + col + 1 < tile_count && row % col != (col - 1)) {
        tilesAreAdjacent.push_back(&(tiles[row + col + 1]));
    }
    if (row + col >= 0 && row + col < tile_count) {
        tilesAreAdjacent.push_back(&(tiles[row + col]));
    }
    if (row + col - 1 >= 0 && row + col - 1 < tile_count && row % col != 0) {
        tilesAreAdjacent.push_back(&(tiles[row + col - 1]));
    }
    if (row - col + 1 >= 0 && row - col < tile_count && row % col != (col - 1)) {
        tilesAreAdjacent.push_back(&(tiles[row - col + 1]));
    }
    if (row - col >= 0 && row - col < tile_count) {
        tilesAreAdjacent.push_back(&(tiles[row - col]));
    }
    if (row - col - 1 >= 0 && row - col - 1 < tile_count && row % col != 0) {
        tilesAreAdjacent.push_back(&(tiles[row - col - 1]));
    }

}
void Tile::placeFlag() {
    hasFlag = true;
}

void Tile::removeFlag() {
    hasFlag = false;
    }

sf::Sprite Tile::getShow() {
    //shows if the tile has been revealed
    if (isShown) {
        return tileOpenedSprite;
    }
    else
        return tileClosedSprite;
}



