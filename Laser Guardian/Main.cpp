#include <iostream>
#include "MainMenu.h"
#include "Game.h"
#include "Background.h"
#include "Credits.h"
#include <SFML/Audio.hpp> 

using namespace sf;

int main() {
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Laser Guardian");
    Clock clock;
    MainMenu mainMenu(window.getSize().x, window.getSize().y);
    Background background(window.getSize());
    //Menu screen background texture Initialisation
    sf::Texture bgLayerTexture;
    bgLayerTexture.loadFromFile("Sprites/background1.png");
    background.addLayer(bgLayerTexture, 8.0f);

    sf::Texture bgLayerTexture3;
    bgLayerTexture3.loadFromFile("Sprites/menuplanets.png");
    background.addLayer(bgLayerTexture3, 8.0f);

    sf::Texture bgLayerTexture2;
    bgLayerTexture2.loadFromFile("Sprites/background2.png");
    background.addLayer(bgLayerTexture2, 25.0f);

    sf::Texture bgLaser3Texture;
    bgLaser3Texture.loadFromFile("Sprites/background3.png");
    background.addLayer(bgLaser3Texture, 50.0f);

    // Load background music
    sf::Music backgroundMusic;
    if (!backgroundMusic.openFromFile("Sounds/backgroundmusic.ogg")) {
        std::cerr << "Error loading background music" << std::endl;
        return -1;
    }
    backgroundMusic.setLoop(true);  // Loop the music
    backgroundMusic.play();


    while (window.isOpen()) {
        MenuResult result = mainMenu.processInput(window);
        float deltaTime = clock.restart().asSeconds();
        background.update(deltaTime);

        switch (result) {
        case MenuResult::Play:
            {
                Game(window);
            }
            break;
        case MenuResult::Exit:
            window.close();
            break;

        case MenuResult::Credits: {
            Credits credits(window.getSize().x, window.getSize().y);
            while (window.isOpen()) {  // Keep this loop within window.isOpen()
                sf::Event event;
                while (window.pollEvent(event)) {
                    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                        result = MenuResult::Nothing;
                        break;
                    }
                    else if (event.type == sf::Event::Closed) {
                        window.close();
                    }
                }
                if (result == MenuResult::Nothing) break;
                credits.draw(window);
            }
            break;
        }
        case MenuResult::Nothing:
            break;
        }
        window.clear(sf::Color::Black);
        
        background.update(deltaTime);
        
        background.draw(window);
        mainMenu.draw(window);
        window.display();
    }

    return 0;
}