#pragma once
#include <map>
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
	void loadTexture(std::string path);

public:
	//Functions
	std::map<std::string, sf::Sprite>::iterator loadSprite(std::string path/*, sf::IntRect rect*/); //�������� �������, ���������� �������� �� ������ � ������������� �������, ���� ��� ���, �� ������� �����
	std::map<std::string, sf::Font>::iterator loadFont(std::string path); //�������� ������
};
