#pragma once
#include <SFML/Graphics.hpp>

class Credits {
public:
    Credits(float width, float height);
    void draw(sf::RenderWindow& window);

private:
    sf::Font font;
    sf::Text creditsText;
};
