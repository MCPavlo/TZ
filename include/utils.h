#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include <iostream>

extern std::vector<sf::Color> colors;
const int freeColorIndex = 9;

std::string getColorName(const sf::Color& color);
void shuffleColors(std::vector<sf::Color>& colors);