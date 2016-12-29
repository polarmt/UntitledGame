#include <SFML/Graphics.hpp>
#include <map>
#include <vector>
#include "Hero.h"
#include "Environment.h"
#include "TextureManager.h"
#include "Foreign.h"

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
	std::vector<Block> blocks;
	TextureManager textures;
	bool fall = true;
	textures.addTexture("dud.png");
	textures.addTexture("sample_spritesheet.png");
	sf::Sprite block(textures.loadTexture("dud.png"));
	sf::Sprite test(textures.loadTexture("sample_spritesheet.png"), sf::IntRect(0, 0, 64, 64));
	test.setPosition(150, 150);
	block.setPosition(150, 150);

	Block b({ 1000, 50 }, { 0, 500 });
	Foreign missile({ 500, 460});
	Block platform({ 100, 100 }, { 540, 400 });
	int curr = 0; // index of the current block
	blocks.push_back(b);
	blocks.push_back(platform);
	Hero p({ 0, 250 }, textures.loadTexture("sample_spritesheet.png"));
	
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
		bool collisions = false; //tells us whether collisions have occurred
		bool move = true; // checks if the player is eligible to move or not

		missile.fire();
		//Events
		sf::Event event;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !jumping) {
			p.move({ 0, jumpSpeed });
			jumping = true;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			p.setTextureRect(sf::IntRect(animation * 64, 0, 64, 64));
			for (int i = 0; i < blocks.size(); i++) {
				if (curr != i && blocks[i].colliding(&p, 'l')) {
					move = false;
				}
			}
			if (move) {
				p.move({ moveSpeed, 0 });
			}
			if (!jumping && !blocks[0].colliding(&p, 'l')) {
				jumpSpeed = 0;
				jumping = true;
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			p.setTextureRect(sf::IntRect(animation * 64, 64, 64, 64));
			for (int i = 0; i < blocks.size(); i++) {
				if (curr != i && blocks[i].colliding(&p, 'r')) {
					move = false;
				}
			}
			if (move) {
				p.move({ -moveSpeed, 0 });
			}
			if (!jumping && !blocks[0].colliding(&p, 'r')) {
				jumpSpeed = 0;
				jumping = true;
			}
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
		if (fall && !jumping && !sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			if (p.getY() < b.getY()) {
				fallSpeed += gravity;
				p.move({ 0, fallSpeed });
			}
			else {
				fallSpeed = 0;
				fall = false;
			}
		}
		else if(jumping) {
			for (int i = 0; i < blocks.size(); i++) {
				if (!blocks[i].colliding(&p, 't')) {
					jumpSpeed += gravity;
					p.move({ 0, jumpSpeed });
				}
				else {
					p.setY(blocks[i].getY());
					jumpSpeed = -20;
					jumping = false;
					curr = i;
					break;
				}
			}
		}

		//std::cout << cl.getElapsedTime().asMicroseconds() << std::endl;
		cl.restart();
		
		if (p.foreignInteract(missile)) {
			p.takeDamage(5);
		}


		//Draw
		window.clear();

		window.draw(block);
		window.draw(test);
		platform.draw(window);
		missile.draw(window);
		b.draw(window);
		p.draw(window);

		window.display();
	}

	return 0;
}