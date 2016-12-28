#include <iostream>
#include <map>
#include <SFML\Graphics.hpp>

class TextureManager {
	std::map<std::string, sf::Texture*> textureMap;

public:
	const void addTexture(const std::string &fileName);
	const sf::Texture &loadTexture(const std::string &fileName);
};
