#include <iostream>
#include <SFML/Graphics.hpp>
#ifndef TILE_H
#define TILE_H
class GameBoard;
enum class State {
    Hidden,
    Revealed,
    Flagged
};

class Tile {
public:
    bool hasMine;
    bool hasFlag;
    bool isShown;
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
    std::vector<sf::Sprite> numbersForBoard;
    Tile();
    void revealTile(bool tilereveal);
    void setsState(bool stateofMine);
    bool getMineStat();
    bool gettileRevealed();
    bool getFlagStat();
    bool debugger;
    bool loser;
    std::vector<sf::Sprite> numbertiles;
    std::vector<Tile*> tilesAreAdjacent;
    std::vector<Tile*> minesAreAdjacent;
    void Draw(sf::RenderWindow& window);
    void setpos(float x, float y);
    void minesadjacent(std::vector<Tile>& tiles, int x, int columns, int tile_count);
    void findadjoverall(std::vector<Tile>& tiles, int x, int columns, int tile_count);
    sf::RectangleShape getTile() const {
        sf::RectangleShape tile(sf::Vector2f(30, 30));
        tile.setOutlineColor(sf::Color::Black);
        return tile;
    }
    void removeFlag();
    void placeFlag();
    sf::Sprite getShow();
};



#endif // TILE_H

