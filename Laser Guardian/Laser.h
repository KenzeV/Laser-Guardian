#pragma once
#include "SFML/Graphics.hpp"

class Laser {
public:
    sf::Sprite laser;

    Laser(sf::Texture* texture, sf::Vector2f pos);
    ~Laser();
};


