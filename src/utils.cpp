#include "utils.h"
#include <algorithm>
#include <random>

sf::Color Brown(165, 42, 42);
sf::Color Gray(128, 128, 128);
sf::Color Pink(255, 192, 203);


std::vector<sf::Color> colors = {sf::Color::White, sf::Color::Black, Brown, sf::Color::Blue, sf::Color::Cyan,
                                 sf::Color::Red, sf::Color::Yellow, sf::Color::Green, Gray, Pink};

std::vector<std::pair<sf::Color, std::string>> colorNames = {
        {sf::Color::White, "White"},
        {sf::Color::Black, "Black"},
        {Brown, "Brown"},
        {sf::Color::Blue, "Blue"},
        {sf::Color::Cyan, "Cyan"},
        {sf::Color::Red, "Red"},
        {sf::Color::Yellow, "Yellow"},
        {sf::Color::Green, "Green"},
        {Gray, "Gray"},
        {Pink, "Pink"}
};

std::string getColorName(const sf::Color& color) {
    for (const auto& pair : colorNames) {
        if (pair.first == color) {
            return pair.second;
        }
    }
    return "Unknown";
}

void shuffleColors(std::vector<sf::Color>& colors) {
    std::random_device rd;
    std::mt19937 shuffler(rd());
    std::shuffle(colors.begin(), colors.end(), shuffler);
}