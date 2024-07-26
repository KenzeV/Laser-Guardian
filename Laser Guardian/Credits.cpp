#include "Credits.h"

Credits::Credits(float width, float height) {
    // Load the font
    if (!font.loadFromFile("Fonts/lasercorps.ttf")) {
        // Handle error
    }

    // Set up the credits text
    creditsText.setFont(font);
    creditsText.setString("Credits\n\nDeveloper: Michael Lewsey\n\Assets: opengameart.org/\n\nMusic: Orbital Colossus by Matthew Pablo (opengameart.org)\n\nPress ESC to Return");
    creditsText.setCharacterSize(20);
    creditsText.setFillColor(sf::Color::White);
    creditsText.setStyle(sf::Text::Bold);

    // Center the text
    sf::FloatRect textRect = creditsText.getLocalBounds();
    creditsText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    creditsText.setPosition(sf::Vector2f(width / 2.0f, height / 2.0f));
}

void Credits::draw(sf::RenderWindow& window) {
    window.clear();
    window.draw(creditsText);
    window.display();
}
