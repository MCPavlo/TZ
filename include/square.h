#pragma once
#include <SFML/Graphics.hpp>
#include <string>

struct Square {
    sf::RectangleShape shape = sf::RectangleShape(sf::Vector2f(100.0f, 100.0f));
    std::string colorName;
    sf::Color color;
    sf::Text text;
};

void initializeSquare(Square& square, sf::Color color, sf::Font& font, std::string colorName);