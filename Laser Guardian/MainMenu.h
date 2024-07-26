#pragma once
#include <SFML/Graphics.hpp>

enum class MenuResult { Nothing, Exit, Play, Credits };

class MainMenu {
public:
    MainMenu(float width, float height);
    void draw(sf::RenderWindow& window);
    MenuResult processInput(sf::RenderWindow& window);

private:
    sf::Font menuFont;
    sf::Font titleFont;
    sf::Text menuItems[3];
    sf::Texture backgroundTexture;
    sf::Sprite backgroundImage;
    int selectedItemIndex;
    sf::Text title;
    
};
