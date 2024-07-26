#pragma once
#include "Laser.h" 
#include "SFML/Graphics.hpp"
#include <vector>


class Player {
public:
    sf::Sprite playerSprite;
    sf::Texture* texture;
    int playerHP;
    int playerMaxHP;
    std::vector<Laser> lasers;

    Player(sf::Texture* texture);
    ~Player();
};

