#include <iostream>
#include <SFML\Graphics.hpp>

class Hero {
	sf::RectangleShape hero; //hitbox 
	sf::Texture heroTexture;
	sf::Sprite heroSprite;
public:
	Hero(sf::Vector2f size, sf::Vector2f newPos, const sf::Texture& newTexture) {
		hero.setSize(size);
		hero.setPosition(newPos);
		hero.setFillColor(sf::Color::Red);

		heroSprite.setPosition(newPos);
		heroTexture = newTexture;
		heroSprite.setTexture(heroTexture);
		heroSprite.setTextureRect(sf::IntRect(0, 0, 64, 64));
	}
	void setTextureRect(sf::IntRect &newRect) {
		heroSprite.setTextureRect(newRect);
	}

	void draw(sf::RenderWindow &window) {
		window.draw(heroSprite);
		window.draw(hero);
	}

	void move(sf::Vector2f distance) {
		heroSprite.move(distance);
	}

	int getY() {
		return heroSprite.getPosition().y;
	}
};