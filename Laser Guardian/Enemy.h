#pragma once
#include "SFML/Graphics.hpp"

class Enemy {
public:
    sf::Sprite enemySprite;
    int enemyHP;
    int enemyMaxHP;

    Enemy(sf::Texture* texture, sf::Vector2u windowSize);
    ~Enemy();
};


