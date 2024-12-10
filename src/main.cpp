#include <SFML/Graphics.hpp>
#include <chrono>
#include "square.h"
#include "api.h"
#include "utils.h"


int main() {
    sf::RenderWindow window(sf::VideoMode(800, 800), "Squares", sf::Style::Titlebar | sf::Style::Close);

    sf::Font font;
    if (!font.loadFromFile("assets/arialmt.ttf")) {
        return -1;
    }

    std::vector<Square> squares(9);

    shuffleColors(colors);

    for (int i = 0; i < 9; ++i) {
        squares[i].color = colors[i];
        squares[i].shape.setFillColor(squares[i].color);
        squares[i].colorName = getColorName(squares[i].color);

        squares[i].text.setFont(font);
        squares[i].text.setString(squares[i].colorName);
        squares[i].text.setCharacterSize(18);
        squares[i].text.setFillColor(sf::Color::Black);
        squares[i].text.setOutlineColor(sf::Color::White);
        squares[i].text.setOutlineThickness(1.0f);
        squares[i].text.setPosition(i % 3 * 100.0f + 10.0f, i / 3 * 100.0f + 40.0f);
    }

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            squares[i * 3 + j].shape.setPosition(j * 100.0f, i * 100.0f);
        }
    }

    sf::Color freeColor = colors[freeColorIndex];

    int clickCount = 0;
    sf::Text clickCounterText;
    clickCounterText.setFont(font);
    clickCounterText.setCharacterSize(24);
    clickCounterText.setFillColor(sf::Color::White);
    clickCounterText.setOutlineColor(sf::Color::Black);
    clickCounterText.setOutlineThickness(1.0f);
    clickCounterText.setPosition(10.0f, 750.0f);
    clickCounterText.setString("Clicks: " + std::to_string(clickCount));

    sf::Text timeText;
    timeText.setFont(font);
    timeText.setCharacterSize(24);
    timeText.setFillColor(sf::Color::White);
    timeText.setOutlineColor(sf::Color::Black);
    timeText.setOutlineThickness(1.0f);

    sf::Text temperatureText;
    temperatureText.setFont(font);
    temperatureText.setCharacterSize(24);
    temperatureText.setFillColor(sf::Color::White);
    temperatureText.setOutlineColor(sf::Color::Black);
    temperatureText.setOutlineThickness(1.0f);

    // Время из API (получается один раз)
    std::string initialTime = getCurrentTime();

    std::tm initialTM = {};
    sscanf_s(initialTime.c_str(), "%d:%d:%d", &initialTM.tm_hour, &initialTM.tm_min, &initialTM.tm_sec);

    // Текущее системное время
    time_t systemTime = std::time(nullptr);
    std::tm* sysTM = std::localtime(&systemTime);
    initialTM.tm_mday = sysTM->tm_mday;
    initialTM.tm_mon = sysTM->tm_mon;
    initialTM.tm_year = sysTM->tm_year;

    time_t initialTime_t = std::mktime(&initialTM);

    time_t offset = initialTime_t - systemTime;
    std::string initialTemperature = getCurrentTemperature();
    temperatureText.setString("Temperature: " + initialTemperature);

    auto lastTemperatureUpdate = std::chrono::steady_clock::now();

    while (window.isOpen()) {
        sf::Event evnt;
        while (window.pollEvent(evnt)) {
            switch (evnt.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::MouseButtonPressed:
                    if (evnt.mouseButton.button == sf::Mouse::Left) {
                        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                        for (auto& square : squares) {
                            if (square.shape.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                                sf::Color previousFreeColor = freeColor;
                                freeColor = square.color;
                                square.color = previousFreeColor;
                                square.shape.setFillColor(square.color);
                                square.colorName = getColorName(square.color);
                                square.text.setString(square.colorName);
                                clickCount++;
                                clickCounterText.setString("Clicks: " + std::to_string(clickCount));
                                break;
                            }
                        }
                    }
                    break;
            }
        }

        time_t currentTime = std::time(nullptr) + offset;
        std::tm* localTime = std::localtime(&currentTime);

        char buffer[128];
        std::strftime(buffer, sizeof(buffer), "%H:%M:%S", localTime);
        timeText.setString("Time: " + std::string(buffer));

        // Обновляется каждые 30 минут.
        auto now = std::chrono::steady_clock::now();
        if (std::chrono::duration_cast<std::chrono::minutes>(now - lastTemperatureUpdate).count() >= 30) {
            initialTemperature = getCurrentTemperature();
            temperatureText.setString("Temperature: " + initialTemperature);
            lastTemperatureUpdate = now;
        }

        sf::FloatRect timeBounds = timeText.getLocalBounds();
        sf::FloatRect tempBounds = temperatureText.getLocalBounds();
        float timeX = window.getSize().x - timeBounds.width - 10.0f;
        float tempX = window.getSize().x - tempBounds.width - 10.0f;
        float timeY = window.getSize().y - timeBounds.height - 10.0f;
        float tempY = window.getSize().y - tempBounds.height - 40.0f;

        timeText.setPosition(timeX, timeY);
        temperatureText.setPosition(tempX, tempY);

        window.clear();

        for (const auto& square : squares) {
            window.draw(square.shape);
            window.draw(square.text);
        }

        window.draw(clickCounterText);
        window.draw(timeText);
        window.draw(temperatureText);

        window.display();
    }

    std::cout << "Time API calls: " << apiCounters.timeApiCalls << std::endl;
    std::cout << "Temperature API calls: " << apiCounters.temperatureApiCalls << std::endl;

    return 0;
}