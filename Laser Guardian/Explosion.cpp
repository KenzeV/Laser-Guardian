#include "Explosion.h"

Explosion::Explosion(sf::Texture* texture, sf::Vector2f position, float scale)
    : totalTime(0.0f), switchTime(0.1f), imageCount(4), finished(false) {
    sprite.setTexture(*texture);
    sprite.setPosition(position);
    // Set explosion scale factor 
    sprite.setScale(scale, scale); 
    currentImage.x = 0;
    currentImage.y = 0;
    sprite.setTextureRect(sf::IntRect(currentImage.x * 64, currentImage.y * 64, 64, 64));
}

void Explosion::update(float deltaTime) {
    totalTime += deltaTime;
    if (totalTime >= switchTime) {
        totalTime -= switchTime;
        currentImage.x++;
        if (currentImage.x >= imageCount) {
            currentImage.x = 0;
            currentImage.y++;
            if (currentImage.y >= imageCount) {
                finished = true;
            }
        }
        sprite.setTextureRect(sf::IntRect(currentImage.x * 64, currentImage.y * 64, 64, 64));
    }
}

void Explosion::draw(sf::RenderWindow& window) {
    if (!finished) {
        window.draw(sprite);
    }
}

bool Explosion::isFinished() const {
    return finished;
}