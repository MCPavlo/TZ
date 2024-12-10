#include "square.h"
#include "utils.h"

void initializeSquare(Square& square, sf::Color color, sf::Font& font, std::string colorName) {
    square.color = color;
    square.shape.setFillColor(square.color);
    square.colorName = colorName;
    square.text.setFont(font);
    square.text.setString(colorName);
    square.text.setCharacterSize(18);
    square.text.setFillColor(sf::Color::Black);
    square.text.setOutlineColor(sf::Color::White);
    square.text.setOutlineThickness(1.0f);
}