#include "Resources.h"
//Functions
void Resources::loadTexture(std::string path)
{
	if (textures.find(path) == textures.end()) //if texture was not found - add it
	{
		sf::Texture texture;
		texture.loadFromFile(path);
		textures.emplace(path, texture);
	}
}

std::map<std::string, sf::Sprite>::iterator Resources::loadSprite(std::string path/*, sf::IntRect rect*/)
{
	if (sprites.find(path) == sprites.end()) //if sprite was not found - add it
	{
		loadTexture(path);
		sprites.emplace(path, sf::Sprite(textures.find(path)->second));
		//sprites[path].setTextureRect(rect);
		sprites[path].setPosition(0, 0);
	}
	return sprites.find(path); //returns an iterator
}

std::map<std::string, sf::Font>::iterator Resources::loadFont(std::string path)
{
	if (fonts.find(path) == fonts.end())//if font was not found - add it
	{
		sf::Font font;
		font.loadFromFile(path);
		fonts.emplace(path, font);
	}
	return fonts.find(path); //returns an iterator
}
