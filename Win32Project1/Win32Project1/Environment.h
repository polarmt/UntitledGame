#include <iostream>
#include <SFML\Graphics.hpp>

class Block {
	sf::RectangleShape block;
	sf::Sprite blockSprite;
public:
	Block(sf::Vector2f size, sf::Vector2f newPos) {
		block.setSize(size);
		block.setPosition(newPos);
		block.setFillColor(sf::Color::Red);
	}

	void move(sf::Vector2f distance) {
		block.move(distance);
	}

	void draw(sf::RenderWindow &window) {
		window.draw(block);
	}

	bool colliding(Hero* hero, char flag) {
		if (flag == 't') {
			return hero->getY() >= block.getPosition().y - 50 &&
				hero->getX() >= block.getPosition().x &&
				hero->getX() <= block.getPosition().x + block.getSize().x;
		}
		else if (flag == 'r' || flag == 'l') {
			return hero->getX() <= block.getPosition().x + block.getSize().x &&
				hero->getX() >= block.getPosition().x &&
				hero->getY() >= block.getPosition().y - 50 &&
				hero->getY() <= block.getPosition().y + block.getSize().y;
		}
		else if (flag == 'b') {
			return hero->getY() <= block.getPosition().y + block.getSize().y &&
				hero->getX() >= block.getPosition().x &&
				hero->getX() <= block.getPosition().x + block.getSize().x;
		}
		else {
			return false;
		}
	}

	int getY() {
		return block.getPosition().y - 50;
	}

	//landing location
	int getLand() {
		return block.getPosition().y - 50;
	}

	~Block() {
		std::cout << "Block is destroyed" << std::endl;
	}
};