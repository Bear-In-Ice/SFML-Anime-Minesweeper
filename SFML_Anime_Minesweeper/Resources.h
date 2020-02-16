#pragma once
#include <map>
#include <iterator>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
class Resources
{
private:
	//Containers
	std::map<std::string, sf::Texture> textures;
	std::map<std::string, sf::Sprite> sprites;
	std::map<std::string, sf::Font> fonts;

	//Function
	void LoadTexture(std::string path);

public:
	//Functions
	std::map<std::string, sf::Sprite>::iterator LoadSprite(std::string path); 
	std::map<std::string, sf::Font>::iterator LoadFont(std::string path); 
};
