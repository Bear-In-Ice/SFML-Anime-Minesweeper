#include "Field.h"
Field::Field(int fieldSize_x, int fieldSize_y, Resources& resources)
{
	this->initFieldSize(fieldSize_x, fieldSize_y);
	this->initFieldGrids();
	//this->initSprite_Texture();
	sprite_iterator = resources.loadSprite("images/tiles1.png");
}


//Initialization
void Field::initFieldSize(int fieldSize_x, int fieldSize_y) //initializes field size
{
	this->fieldSize_x = fieldSize_x;
	this->fieldSize_y = fieldSize_y;
}

void Field::initFieldGrids() //initializes the values in the "grids"
{
	randomValueGrid = new int* [fieldSize_x];
	for (int i = 0; i < fieldSize_x; i++)
		randomValueGrid[i] = new int[fieldSize_y];

	if (randomValueGrid)
		for (int i = 0; i < fieldSize_x; i++)
			for (int j = 0; j < fieldSize_y; j++)
				randomValueGrid[i][j] = 0;

	/*____________________________________________________*/
	displayGrid = new int* [fieldSize_x];
	for (int i = 0; i < fieldSize_x; i++)
		displayGrid[i] = new int[fieldSize_y];

	if(displayGrid)
	for (int i = 0; i < fieldSize_x; i++)
		for (int j = 0; j < fieldSize_y; j++)
			this->displayGrid[i][j] = 10;
}

void Field::initSprite_Texture() //initializes sprite and texture for field
{
	this->field_texture.loadFromFile("images/tiles1.png");
	this->field_sprite.setTexture(this->field_texture);
	field_sprite.setTextureRect(sf::IntRect(1 * 25, 0, 25, 25));
}


//Functions
void Field::Print_randomValueGrid()
{
	for (int i = 0; i < fieldSize_x; i++) {
		for (int j = 0; j < fieldSize_y; j++)
			std::cout << randomValueGrid[i][j];
		std::cout << std::endl;
	}
}

void Field::Print_displayGrid()
{
	for (int i = 0; i < fieldSize_x; i++) {
		for (int j = 0; j < fieldSize_y; j++)
			std::cout << displayGrid[i][j];
		std::cout << std::endl;
	}
}

void  Field::draw_field(sf::RenderTarget& target)
{
	for (int i = 0; i < this->fieldSize_x; i++)
		for (int j = 0; j < this->fieldSize_y; j++)
		{
			(*sprite_iterator).second.setTextureRect(sf::IntRect(displayGrid[i][j] * 25, 0, 25, 25));
			(*sprite_iterator).second.setPosition(((i * 25) + (700 / 4)), (j * 25) + 50);
			target.draw((*sprite_iterator).second);
		}
}
