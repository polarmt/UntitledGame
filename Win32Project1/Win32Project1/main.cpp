#include <SFML/Graphics.hpp>
#include <map>
#include "Hero.h"
#include "Environment.h"
#include "TextureManager.h"

int main()
{
	//Window
	float height = 1080;
	float width = 540;
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	sf::RenderWindow window;
	window.create(sf::VideoMode(height, width, desktop.bitsPerPixel), "Untitled Game");	
	window.setFramerateLimit(60);

	//Objects

	TextureManager textures;
	textures.addTexture("dud.png");
	textures.addTexture("sample_spritesheet.png");
	sf::Sprite block(textures.loadTexture("dud.png"));
	sf::Sprite test(textures.loadTexture("sample_spritesheet.png"), sf::IntRect(0, 0, 64, 64));
	test.setPosition(150, 150);
	block.setPosition(150, 150);

	Block b({ 1000, 50 }, { 0, 500 });
	Hero p({ 50, 50 }, { 0, 250 }, textures.loadTexture("sample_spritesheet.png"));

	//Logic variables
	bool jumping = false;
	int animation = 0;
	int delayCounter = 0;

	float jumpSpeed = -0.01;
	float fallSpeed = 0;
	const float gravity = 1.0;
	const float moveSpeed = 4.5;

	sf::Clock cl; 

	while (window.isOpen()) {
		//Events
		sf::Event event;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !jumping) {
			p.move({ 0, gravity });
			jumping = true;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			p.setTextureRect(sf::IntRect(animation * 64, 0, 64, 64));
			p.move({ moveSpeed, 0 });
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			p.setTextureRect(sf::IntRect(animation * 64, 64, 64, 64));
			p.move({ -moveSpeed, 0 });
		}
			
		
		
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		//Logic
		//Animation

		delayCounter++;
		if (delayCounter % 5 == 0) {
			animation++;
		}
		if (animation == 2) {
			animation = 0;
		}

		//Gravity
		if (!jumping && !sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			if (p.getY() < b.getY()) {
				fallSpeed += gravity;
				p.move({ 0, fallSpeed });
			}
			else {
				fallSpeed = 0;
			}
		}
		else {
			if (p.getY() < b.getY() || jumpSpeed < 1) {
				jumpSpeed += gravity;
				p.move({ 0, jumpSpeed });
			}
			else {
				p.setY(b.getY());
				jumpSpeed = -10;
				jumping = false;
			}
		}

		std::cout << cl.getElapsedTime().asMicroseconds() << std::endl;
		cl.restart();
		

		//Draw
		window.clear();

		window.draw(block);
		window.draw(test);
		b.draw(window);
		p.draw(window);

		window.display();
	}

	return 0;
}