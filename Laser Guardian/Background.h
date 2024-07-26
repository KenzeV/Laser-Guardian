#pragma once
#include "SFML/Graphics.hpp"
#include <vector>

class Background {
public:
    // Constructor that takes window size
    Background(sf::Vector2u windowSize);

    void addLayer(const sf::Texture& texture, float speed);
    void update(float deltaTime);
    void draw(sf::RenderWindow& window);

private:
    struct Layer {
        sf::Sprite sprite1; // Sprite for the first layer
        sf::Sprite sprite2; // sprite for the second layer
        float speed;
    };

    std::vector<Layer> layers;
    sf::Vector2u windowSize; // Stored window size for calculations
};
