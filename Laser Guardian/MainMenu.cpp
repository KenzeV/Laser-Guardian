
#include "MainMenu.h"

MainMenu::MainMenu(float width, float height) {

    
    //initialising Font
    titleFont.loadFromFile("Fonts/laserfont.ttf");
    menuFont.loadFromFile("Fonts/lasercorps.ttf");
    //Main Menu Title
    title.setFont(titleFont);
    title.setString("lASER GUARDIAN"); 
    title.setFillColor(sf::Color::Red);
    float centerX = width / 2;
    float centerY = height / 2;
    sf::FloatRect titleRect = title.getLocalBounds();
    title.setOrigin(titleRect.left + titleRect.width / 2.0f, titleRect.top + titleRect.height / 2.0f);
    title.setPosition(sf::Vector2f(centerX - 150, centerY - 150));
    title.setCharacterSize(50);
    // Setting up the menu items with font, color, and string
    for (int i = 0; i < 3; i++) {
        menuItems[i].setFont(menuFont);
        menuItems[i].setFillColor(sf::Color::White);
        menuItems[i].setCharacterSize(30);
    }

    menuItems[0].setString("Start Game");
    menuItems[1].setString("Exit");
    menuItems[2].setString("Credits");
    // Centering each menu item based on its size
    for (int i = 0; i < 3; i++) {
        sf::FloatRect textRect = menuItems[i].getLocalBounds();
        menuItems[i].setOrigin(textRect.left + textRect.width/2.0f,
                               textRect.top  + textRect.height/2.0f);
        menuItems[i].setPosition(sf::Vector2f(centerX, centerY + (i - 1) * 50));  // Adjust positions to fit 3 items
    }

    selectedItemIndex = 0;
}



void MainMenu::draw(sf::RenderWindow& window) {
    window.draw(title);
    for (int i = 0; i < 3; i++) {
        if (i == selectedItemIndex) {
            // Highlight the selected item
            menuItems[i].setFillColor(sf::Color::Yellow);
        }
        else {
            menuItems[i].setFillColor(sf::Color::White);
        }
        window.draw(menuItems[i]);

    }
}

MenuResult MainMenu::processInput(sf::RenderWindow& window) {
    sf::Event event;
    while (window.pollEvent(event)) {
        switch (event.type) {
        case sf::Event::KeyReleased:
            switch (event.key.code) {
            case sf::Keyboard::Up:
            case sf::Keyboard::W: // Add W key for moving up
                if (selectedItemIndex > 0)
                    selectedItemIndex--;
                break;
            case sf::Keyboard::Down:
            case sf::Keyboard::S: // Add S key for moving down
                if (selectedItemIndex < 1)
                    selectedItemIndex++;
                break;
            case sf::Keyboard::Return:
                switch (selectedItemIndex) {
                case 0:
                    return MenuResult::Play;
                case 1:
                    return MenuResult::Exit;
                case 2:
                    return MenuResult::Credits;
                }

                break;
            default:
                break;
            }
            break;
            //mouse click for menu
        case sf::Event::MouseButtonReleased:
            if (event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

                
                if (menuItems[0].getGlobalBounds().contains(mousePosF)) {
                    return MenuResult::Play;
                }
                else if (menuItems[1].getGlobalBounds().contains(mousePosF)) {
                    
                    return MenuResult::Exit;
                }
                else if (menuItems[2].getGlobalBounds().contains(mousePosF)) {
                    return MenuResult::Credits;  // Return Credits result
                   }
            }
            break;
        case sf::Event::Closed:
            return MenuResult::Exit;
        default:
            break;
        }
    }
    return MenuResult::Nothing;

}

