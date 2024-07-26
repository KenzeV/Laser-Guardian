#pragma once
#include <SFML/Graphics.hpp>

class Explosion {
public:
    Explosion(sf::Texture* texture, sf::Vector2f position, float scale = 1.0f);
    void update(float deltaTime);
    void draw(sf::RenderWindow& window);
    bool isFinished() const;

private:
    sf::Sprite sprite;
    float totalTime;
    float switchTime;
    int imageCount;
    sf::Vector2i currentImage;
    bool finished;
};

