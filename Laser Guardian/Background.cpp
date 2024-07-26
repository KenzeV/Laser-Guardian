#include "Background.h"

Background::Background(sf::Vector2u windowSize) : windowSize(windowSize) {}

void Background::addLayer(const sf::Texture& texture, float speed) {
    Layer layer;
    layer.sprite1.setTexture(texture);
    layer.sprite2.setTexture(texture);

    
    layer.sprite2.setPosition(texture.getSize().x, 0);

    layer.speed = speed;
    layers.push_back(layer);
}
//background update for parallax effect
void Background::update(float deltaTime) {
    for (auto& layer : layers) {
        
        sf::Vector2f position1 = layer.sprite1.getPosition();
        sf::Vector2f position2 = layer.sprite2.getPosition();

        position1.x -= layer.speed * deltaTime;
        position2.x -= layer.speed * deltaTime;

        
        if (position1.x + layer.sprite1.getGlobalBounds().width < 0) {
            position1.x = position2.x + layer.sprite2.getGlobalBounds().width;
        }

        
        if (position2.x + layer.sprite2.getGlobalBounds().width < 0) {
            position2.x = position1.x + layer.sprite1.getGlobalBounds().width;
        }

        layer.sprite1.setPosition(position1);
        layer.sprite2.setPosition(position2);
    }
}

void Background::draw(sf::RenderWindow& window) {
    for (const auto& layer : layers) {
        window.draw(layer.sprite1);
        window.draw(layer.sprite2);
    }
}
