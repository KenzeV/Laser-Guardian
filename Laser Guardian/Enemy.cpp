#include "Enemy.h"
//Enemy constructor
Enemy::Enemy(sf::Texture* texture, sf::Vector2u windowSize) {
    
    enemyMaxHP = 3;
    enemyHP = enemyMaxHP;
    enemySprite.setTexture(*texture);
    enemySprite.setScale(0.2f, 0.2f);
    enemySprite.setPosition(windowSize.x - enemySprite.getGlobalBounds().width, rand() % (int)(windowSize.y - enemySprite.getGlobalBounds().height));
}

Enemy::~Enemy() {}
