#pragma once
#include <iostream>
#include <ctime>

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
	int numberMines;
	
	//SFML Sprite and Texture
	std::map<std::string, sf::Sprite>::iterator sprite_iterator;
	
	//Initialization
	void InitFieldSize(int fieldSize_x, int fieldSize_y);   //initializes field size
	void InitFieldGrids();                                  //initializes the values in the "grids"
	
public:

	//Constructors/Destructor
	Field(int fieldSize_x, int fieldSize_y, Resources & resources);
	~Field();

	//Functions
	bool CheckWin();
	void Print_randomValueGrid();
	void Print_displayGrid();
	void Draw_field(sf::RenderWindow* target); //SFML window rendering
	void Fill_randomValueGrid(int field_x, int field_y, int games_difficulty);
	void Ride(int field_x, int field_y);
	void Set_flag(int field_x, int field_y);
	int Get_fieldSize_x() { return this->fieldSize_x; }
	int Get_fieldSize_y() { return this->fieldSize_y; }
};
