#include "Player.h"
#include "Enemy.h"
#include "Laser.h"
#include "Background.h"
#include "Explosion.h"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include <SFML/Audio.hpp>
#include <math.h>
#include <cstdlib>
#include <vector>


using namespace sf;


int Game(sf::RenderWindow& window)
{
	
	srand(time(NULL));
	Clock clock;

	window.setFramerateLimit(60);

	//Font Initialisation
	Font font;
	font.loadFromFile("Fonts/laserfont.ttf");

	//Texture Initialisation for enemy and player ship
	Texture playerTex;
	playerTex.loadFromFile("Sprites/playership.png");

	Texture enemyTex;
	enemyTex.loadFromFile("Sprites/enemyship.png");

	Texture laserTex;
	laserTex.loadFromFile("Sprites/playerlaser.png");

	// Load explosion sprite sheet
	std::vector<Explosion> explosions;
	//previous 
	Texture explosionTex;
	explosionTex.loadFromFile("Sprites/explosion.png");

	// Load laser sound
	SoundBuffer laserSoundBuffer;
	laserSoundBuffer.loadFromFile("Sounds/playerlasersound.mp3");
	Sound laserSound;
	laserSound.setBuffer(laserSoundBuffer);

	//Load explosion sound
	SoundBuffer explosionSoundBuffer;
	explosionSoundBuffer.loadFromFile("Sounds/explosionsound.mp3");
	Sound explosionSound;
	explosionSound.setBuffer(explosionSoundBuffer);

	//background initialisation
	Background background(window.getSize());
	sf::Texture bgLayer1Texture;
	bgLayer1Texture.loadFromFile("Sprites/background1.png");
	background.addLayer(bgLayer1Texture, 25.0f); // The speed can be adjusted

	sf::Texture bgLayer2Texture;
	bgLayer2Texture.loadFromFile("Sprites/background2.png");
	background.addLayer(bgLayer2Texture, 50.0f); // Faster layer

	sf::Texture bgLaser3Texture;
	bgLaser3Texture.loadFromFile("Sprites/background3.png");
	background.addLayer(bgLaser3Texture, 75.0f);

	//UI Initialisation
	Text scoreText;
	scoreText.setFont(font);
	scoreText.setCharacterSize(20);
	scoreText.setFillColor(Color::White);
	scoreText.setPosition(10, 10);
	//Game over text init
	Text gameOverMessage;
	gameOverMessage.setFont(font);
	gameOverMessage.setCharacterSize(50);
	gameOverMessage.setFillColor(Color::Red);
	gameOverMessage.setPosition(100, window.getSize().y / 2);
	gameOverMessage.setString("GAME OVER.");
	FloatRect textRect = gameOverMessage.getLocalBounds();
	gameOverMessage.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	gameOverMessage.setPosition(sf::Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2));
	bool gameOver = false;
	//Retry game initialisation
	Text retryMessage;
	retryMessage.setFont(font);
	retryMessage.setCharacterSize(30);
	retryMessage.setFillColor(Color::White);
	retryMessage.setString("Press Y to Retry or N to Exit.");
	FloatRect retryTextRect = retryMessage.getLocalBounds();
	retryMessage.setOrigin(retryTextRect.left + retryTextRect.width / 2.0f, retryTextRect.top + retryTextRect.height / 2.0f);
	retryMessage.setPosition(sf::Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2 + 70)); 
	
	//Pause message initialisation
	Text pauseMessage;
	pauseMessage.setFont(font);
	pauseMessage.setCharacterSize(50);
	pauseMessage.setFillColor(Color::Yellow);
	pauseMessage.setString("PAUSED");
	FloatRect pauseTextRect = pauseMessage.getLocalBounds();
	pauseMessage.setOrigin(pauseTextRect.left + pauseTextRect.width / 2.0f, pauseTextRect.top + pauseTextRect.height / 2.0f);
	pauseMessage.setPosition(sf::Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2));


	//Player Initialisation
	int score = 0;
	Player player(&playerTex);
	int laserFireTimer = 20;
	Text playerHealthText;
	playerHealthText.setFont(font);
	playerHealthText.setCharacterSize(12);
	playerHealthText.setFillColor(Color::White);
	float playerHealthBarVerticalOffset = 10.0f;
	//Centers player at game start
	
	float playerCenterOffset = 25; 
	player.playerSprite.setPosition(playerCenterOffset, window.getSize().y / 2 - player.playerSprite.getGlobalBounds().height / 2);


	//Enemy Initialisation
	int enemySpawnTimer = 0;
	std::vector<Enemy> enemies;
	Text enemyHealthText;
	enemyHealthText.setFont(font);
	enemyHealthText.setCharacterSize(12);
	enemyHealthText.setFillColor(Color::White);

	// Pause state
	bool isPaused = false;

	while (window.isOpen())
	{

		Event event;
		float deltaTime = clock.restart().asSeconds();
		

		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();

			// Handle pause/resume
			if (event.type == Event::KeyPressed && event.key.code == Keyboard::P) {
				isPaused = !isPaused; // Toggle pause state
			}
		}
		if (!isPaused) {

			//player controls if player alive
			if (player.playerHP > 0)
			{


				// Player Controls
				if (Keyboard::isKeyPressed(Keyboard::W) || Keyboard::isKeyPressed(Keyboard::Up))
					player.playerSprite.move(0, -10);
				if (Keyboard::isKeyPressed(Keyboard::A) || Keyboard::isKeyPressed(Keyboard::Left))
					player.playerSprite.move(-10, 0);
				if (Keyboard::isKeyPressed(Keyboard::S) || Keyboard::isKeyPressed(Keyboard::Down))
					player.playerSprite.move(0, 10);
				if (Keyboard::isKeyPressed(Keyboard::D) || Keyboard::isKeyPressed(Keyboard::Right))
					player.playerSprite.move(10, 0);


				//player health bar
				std::string playerHealthDashes;
				for (int hp = 0; hp < player.playerHP; hp++)
				{
					playerHealthDashes += "-"; // Add a dash for each health point of the player
				}
				playerHealthText.setString(playerHealthDashes);
				playerHealthText.setFillColor(sf::Color::Green);

				playerHealthText.setPosition(player.playerSprite.getPosition().x, player.playerSprite.getPosition().y - playerHealthText.getGlobalBounds().height - playerHealthBarVerticalOffset);



				//check collision with window
				if (player.playerSprite.getPosition().x <= 0) //left
					player.playerSprite.setPosition(0, player.playerSprite.getPosition().y);

				if (player.playerSprite.getPosition().x >= window.getSize().x - player.playerSprite.getGlobalBounds().width) //right
					player.playerSprite.setPosition(window.getSize().x - player.playerSprite.getGlobalBounds().width, player.playerSprite.getPosition().y);

				if (player.playerSprite.getPosition().y <= 0) //top
					player.playerSprite.setPosition(player.playerSprite.getPosition().x, 0);

				if (player.playerSprite.getPosition().y >= window.getSize().y - player.playerSprite.getGlobalBounds().height) //bottom
					player.playerSprite.setPosition(player.playerSprite.getPosition().x, window.getSize().y - player.playerSprite.getGlobalBounds().height);


				//Laser Controls
				if (laserFireTimer < 25)
					laserFireTimer++;

				if ((Mouse::isButtonPressed(Mouse::Left) || Keyboard::isKeyPressed(Keyboard::Space)) && laserFireTimer >= 15) //shooting
				{


					Vector2f laserStartPosition = player.playerSprite.getPosition();

					//laser offset to centre laser on player ship
					float laserVerticalOffset = 12.0f;
					float laserHorizontalOffset = 15.0f;
					// Updating the laser's start position with the offset
					laserStartPosition.y += laserVerticalOffset;
					laserStartPosition.x += laserHorizontalOffset;
					// Creating a new laser with the updated starting position
					player.lasers.push_back(Laser(&laserTex, laserStartPosition));
					laserFireTimer = 0;

					//play laser sound
					laserSound.play();
				}


				//lasers
				for (size_t i = 0; i < player.lasers.size(); i++)
				{
					//Lasers movement
					player.lasers[i].laser.move(20, 0);
					//Lasers out of window bounds
					if (player.lasers[i].laser.getPosition().x > window.getSize().x)
					{
						player.lasers.erase(player.lasers.begin() + i);
						break;
					}

					//Enemy Collision
					for (size_t k = 0; k < enemies.size(); k++)
					{
						if (player.lasers[i].laser.getGlobalBounds().intersects(enemies[k].enemySprite.getGlobalBounds()))
						{
							if (enemies[k].enemyHP <= 1)
							{
								score += enemies[k].enemyMaxHP;
								explosionSound.play();
								//explosion animation
								explosions.push_back(Explosion(&explosionTex, enemies[k].enemySprite.getPosition(), 1.5f));


								enemies.erase(enemies.begin() + k);

							}
							else (enemies[k].enemyHP--); //enemy takes damage

							player.lasers.erase(player.lasers.begin() + i);
							break;
						}
					}
				}

				//Enemy Spawn and despawn
				if (enemySpawnTimer < 30)
					enemySpawnTimer++;
				if (enemySpawnTimer >= 20)
				{
					enemies.push_back(Enemy(&enemyTex, window.getSize()));
					enemySpawnTimer = 0;
				}

				for (size_t i = 0; i < enemies.size(); i++)
				{
					enemies[i].enemySprite.move(-5, 0);
					if (enemies[i].enemySprite.getPosition().x <= 0 - enemies[i].enemySprite.getGlobalBounds().width)
					{
						enemies.erase(enemies.begin() + i);
						break;
					}
					if (enemies[i].enemySprite.getGlobalBounds().intersects(player.playerSprite.getGlobalBounds()))
					{
						enemies.erase(enemies.begin() + i);
						player.playerHP--; //PLayer Takes Damage
						if (player.playerHP <= 0) {
							explosionSound.play(); // Play explosion sound when player dies
						}
						break;
					}


				}
				//update explosions
				for (size_t i = 0; i < explosions.size(); i++) {
					explosions[i].update(deltaTime);
					if (explosions[i].isFinished()) {
						explosions.erase(explosions.begin() + i);
						i--;
					}
				}

				//UI Update for player score
				scoreText.setString("Score: " + std::to_string(score));
			}
		}
		//Drawing window
		background.update(deltaTime);
		window.clear(Color::Black);
		background.draw(window);
		window.draw(player.playerSprite);

		//drawing lasers
		for (size_t i = 0; i < player.lasers.size(); i++)
		{
			window.draw(player.lasers[i].laser);
		}
		//enemy health bars
		for (size_t i = 0; i < enemies.size(); i++)
		{
			std::string healthDashes;
			for (int hp = 0; hp < enemies[i].enemyHP; hp++)
			{
				healthDashes += "-"; // 
			}

			enemyHealthText.setString(healthDashes);
			enemyHealthText.setFillColor(sf::Color::Red);
			enemyHealthText.setPosition(enemies[i].enemySprite.getPosition().x, enemies[i].enemySprite.getPosition().y - enemyHealthText.getGlobalBounds().height);
			window.draw(enemyHealthText);
			window.draw(enemies[i].enemySprite);

		}
		for (size_t i = 0; i < explosions.size(); i++) {
			explosions[i].draw(window);
		}
		//UI
		window.draw(scoreText);
		window.draw(playerHealthText);

		//game over state and reset
		if (player.playerHP <= 0) {
			window.draw(gameOverMessage);
			window.draw(retryMessage);
			window.display();
			gameOver = true;

			// Wait for player input
			while (gameOver) {
				while (window.pollEvent(event)) {
					if (event.type == Event::Closed) {
						window.close();
						gameOver = false;
					}
					else if (event.type == Event::KeyPressed) {
						if (event.key.code == Keyboard::Y) {
							// Reset game state and break from loop
							gameOver = false;
							// Reset player, score, enemies, etc. here
							player.playerHP = player.playerMaxHP; // Reset player HP
							score = 0; // Reset score
							enemies.clear(); // Clear existing enemies
							player.lasers.clear(); // Clear existing lasers
						}
						else if (event.key.code == Keyboard::N) {
							window.close();
							gameOver = false;
						}
					}
				}
			}
		}

		window.display();



	}

	return 0;
}