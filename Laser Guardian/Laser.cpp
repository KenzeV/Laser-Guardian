#include "Laser.h"


Laser::Laser(sf::Texture* texture, sf::Vector2f pos) {
    laser.setTexture(*texture);
    laser.setScale(0.1f, 0.1f);
    laser.setPosition(pos);
}

Laser::~Laser() {}
