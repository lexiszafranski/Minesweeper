#include <iostream>
#include <SFML/Graphics.hpp>
#include <ctype.h>
#include <fstream>
#include "gameboard.h"

void setText(sf::Text& text, float x, float y) {
    // they said we need these functions so i am just putting this at the top
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    text.setPosition(sf::Vector2f(x, y));

}
void drawLeaderboard(sf::RenderWindow& window, int width, int height) {
    std::ifstream file("files/leaderboard.txt");
    if (!file.is_open()) {
        std::cerr << "Error: Failed to open leaderboard file" << std::endl;
        return;
    }
    std::vector<std::string> rows;
    std::string row;
    while (std::getline(file, row)) {
        rows.push_back(row);
    }
    sf::Font font;
    if (!font.loadFromFile("files/font.ttf")) {
        std::cerr << "Error: Failed to load font file" << std::endl;
        return;
    }
    sf::RenderWindow leaderboardWindow(sf::VideoMode(width, height), "Leaderboard", sf::Style::Close);
    leaderboardWindow.clear(sf::Color::Blue);
    sf::Text title("LEADERBOARD", font, 20);
    title.setStyle(sf::Text::Bold | sf::Text::Underlined);
    title.setFillColor(sf::Color::White);
    title.setOrigin(title.getLocalBounds().left + title.getLocalBounds().width/2.0f,
                    title.getLocalBounds().top + title.getLocalBounds().height/2.0f);
    title.setPosition(sf::Vector2f(width/2.0f, height/2.0f - 120));

    std::string text;
    const int num_rows = std::min<int>(5, rows.size());
    for (int i = 0; i < num_rows; ++i) {
        text += std::to_string(i + 1) + ".\t" + rows[i] + "\n\n";
    }
    sf::Text leaderboard(text, font, 18);
    leaderboard.setFillColor(sf::Color::White);
    leaderboard.setOrigin(leaderboard.getLocalBounds().left + leaderboard.getLocalBounds().width/2.0f,
                          leaderboard.getLocalBounds().top + leaderboard.getLocalBounds().height/2.0f);
    leaderboard.setPosition(sf::Vector2f(width/2.0f, height/2.0f + 20));
    while (leaderboardWindow.isOpen()) {
        sf::Event event;
        while (leaderboardWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                leaderboardWindow.close();
            }
        }
        leaderboardWindow.clear(sf::Color::Blue);
        leaderboardWindow.draw(title);
        leaderboardWindow.draw(leaderboard);
        leaderboardWindow.display();
    }
}

int main() {

    //intro screen
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window", sf::Style::Close);
    window.clear(sf::Color::Blue);
    sf::Font font;
    if (!font.loadFromFile("files/font.ttf")) {
        // errors are bad mojo
    }
    sf::Text welcomeText("WELCOME TO MINESWEEPER!", font, 24);
    welcomeText.setStyle(sf::Text::Bold | sf::Text::Underlined);
    welcomeText.setFillColor(sf::Color::White);
    welcomeText.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f - 150);
    welcomeText.setOrigin(welcomeText.getLocalBounds().width / 2.0f, welcomeText.getLocalBounds().height / 2.0f);
    sf::Text inputText("Enter your name:", font, 20);
    inputText.setStyle(sf::Text::Bold);
    inputText.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f - 75);
    inputText.setOrigin(inputText.getLocalBounds().width / 2.0f, inputText.getLocalBounds().height / 2.0f);
    sf::Text userInput("", font, 18);
    userInput.setStyle(sf::Text::Bold);
    userInput.setFillColor(sf::Color::Yellow);
    userInput.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f - 45);
    userInput.setOrigin(userInput.getLocalBounds().width / 2.0f, userInput.getLocalBounds().height / 2.0f);
    std::string inputString;
    sf::Text cursor("|", font, 18);
    cursor.setStyle(sf::Text::Bold);
    cursor.setFillColor(sf::Color::Yellow);
    cursor.setPosition(userInput.getPosition().x + userInput.getLocalBounds().width / 2 + 2, userInput.getPosition().y);
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode == 13) { // check if enter
                    window.close();

                    //main window
                    sf::RenderWindow newWindow(sf::VideoMode(800, 600), "New Window");
                    sf::Texture texture;
                    if (!texture.loadFromFile("files/images/tile_hidden.png")) {
                        std::cerr << "Failed to load texture" << std::endl;
                        return 1;
                    }
                    GameBoard board;
                    board.display("files/board_config.cfg");
                    board.Draw(newWindow);
                    while (newWindow.isOpen()) {
                      sf::Event event2;
                        while (newWindow.pollEvent(event2)) {
                            if (event2.type == sf::Event::Closed) {
                                newWindow.close();
                            }
                            if (event2.type == sf::Event::MouseButtonPressed) {
                                sf:: Vector2i spot = sf::Mouse::getPosition(newWindow);
                                if (event2.mouseButton.button == sf::Mouse::Left) {
                                    std::cout << "left 2 pressed";
                                    board.lefty(spot.x, spot.y, event2, newWindow);
                                    //newWindow.clear();
                                    //board.Draw(newWindow);
                                     if (board.leaderboardOn){
                                        drawLeaderboard(newWindow, (800)/2, (600)/2);
                                        board.leaderboardOn = false;
                                    }
                                }
                                if (event2.mouseButton.button == sf::Mouse::Right) {
                                    sf:: Vector2i spot = sf::Mouse::getPosition(newWindow);
                                    std::cout << "right 2 pressed ";
                                    board.righty(spot.x, spot.y, event2, newWindow);
//                                    newWindow.clear();
//                                    board.Draw(newWindow);

                                }
                            }
                            board.checkWin();
                        }
                        newWindow.clear();
                        board.Draw(newWindow);
                        newWindow.display();
                        }
                    }
                if (event.text.unicode < 128 && isalpha(static_cast<char>(event.text.unicode))) {
                    if (event.text.unicode == 8 && !inputString.empty()) {
                        // remove end
                        inputString.pop_back();
                        userInput.setOrigin(userInput.getLocalBounds().width / 2.0f, userInput.getLocalBounds().height / 2.0f);

                    } else if (inputString.size() < 10) {
                        // add new
                        inputString += static_cast<char>(event.text.unicode);
                        userInput.setOrigin(userInput.getLocalBounds().width / 2.0f, userInput.getLocalBounds().height / 2.0f);
                    }
                    // update text
                    userInput.setString(inputString);
                } else if (event.text.unicode == 8 && !inputString.empty()) {
                    inputString.pop_back();
                    userInput.setString(inputString);
                }
            }
        }
        if (inputString.empty()) {
            userInput.setString("");
        }
        else if (!inputString.empty() && inputString.size() == 1) {
            inputString[0] = toupper(inputString[0]);
            userInput.setString(inputString + "|");
        }
        else {
            userInput.setString(inputString + "|");
        }

// drawing
        window.clear(sf::Color::Blue);
        window.draw(welcomeText);
        window.draw(inputText);
        window.draw(userInput);
        window.display();}

    return 0;}