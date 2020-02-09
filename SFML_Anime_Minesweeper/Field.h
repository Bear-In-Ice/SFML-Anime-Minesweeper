#pragma once
#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "Resources.h"

class Field
{
private:
	//Variables
	int fieldSize_x;
	int fieldSize_y;
	int** randomValueGrid;			//for operations related to the game
	int** displayGrid;				//to display
	
	//SFML Sprite and Texture
	sf::Texture field_texture;
	sf::Sprite field_sprite;
	std::map<std::string, sf::Sprite>::iterator sprite_iterator;
	
	//Initialization
	void initFieldSize(int fieldSize_x, int fieldSize_y);   //initializes field size
	void initFieldGrids();                                  //initializes the values in the "grids"
	void initSprite_Texture();                              //initializes sprite and texture for field

public:

	//Constructors/Destructor
	Field(int fieldSize_x, int fieldSize_y, Resources & resources);

	//Functions
	void Print_randomValueGrid();
	void Print_displayGrid();
	void draw_field(sf::RenderTarget& target); //SFML window rendering
};
