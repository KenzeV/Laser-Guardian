#pragma once
#include "Player.h"
//Player constructor
Player::Player(sf::Texture* texture) {
    playerMaxHP = 10;
    playerHP = playerMaxHP;
    texture = texture;
    playerSprite.setTexture(*texture);
    playerSprite.setScale(0.1, 0.1);

}

Player::~Player() {}
