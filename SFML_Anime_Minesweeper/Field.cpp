#include "Field.h"
//Constructors/Destructor
Field::Field(int fieldSize_x, int fieldSize_y, Resources& resources)
{
	this->InitFieldSize(fieldSize_x, fieldSize_y);
	this->InitFieldGrids();
	this->numberMines = 0;
	this->win_or_lose = 0;
	sprite_iterator = resources.LoadSprite("images/tiles1.png");
}

Field::~Field()
{
	for (int i = 0; i < this->fieldSize_x; ++i) {
		delete[] randomValueGrid[i];
	}

	delete[] randomValueGrid;


	for (int i = 0; i < this->fieldSize_x; ++i) {
		delete[] displayGrid[i];
	}
	delete[] displayGrid;
}


//Initialization
void Field::InitFieldSize(int fieldSize_x, int fieldSize_y) //initializes field size
{
	this->fieldSize_x = fieldSize_x;
	this->fieldSize_y = fieldSize_y;
}

void Field::InitFieldGrids() //initializes the values in the "grids"
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

	if (displayGrid)
		for (int i = 0; i < fieldSize_x; i++)
			for (int j = 0; j < fieldSize_y; j++)
				this->displayGrid[i][j] = 10;
}

//Functions
void Field::Print_randomValueGrid()
{
	for (int i = 0; i < fieldSize_y; i++) {
		for (int j = 0; j < fieldSize_x; j++)
			std::cout << randomValueGrid[j][i];
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void Field::Print_displayGrid()
{
	for (int i = 0; i < fieldSize_x; i++) {
		for (int j = 0; j < fieldSize_y; j++)
			std::cout << displayGrid[i][j];
		std::cout << std::endl;
	}
}

void  Field::Draw_field(sf::RenderWindow* target)
{
	for (int i = 0; i < this->fieldSize_x; i++)
		for (int j = 0; j < this->fieldSize_y; j++)
		{
			(*sprite_iterator).second.setTextureRect(sf::IntRect(displayGrid[i][j] * 25, 0, 25, 25));
			(*sprite_iterator).second.setPosition(((i * 25) + (target->getSize().x / 5)), (j * 25) + 75);
			target->draw((*sprite_iterator).second);
		}
}

void Field::Fill_randomValueGrid(int field_x, int field_y, int games_difficulty)
{
	srand(time(NULL));
	int* random_x = new int;
	int* random_y = new int;
	int* temp_gridValue = new int;
	*temp_gridValue = 0;
	switch (games_difficulty)
	{
	case 0:
		for (int i = 0; i < 15;)
		{
			*random_x = rand() % fieldSize_x;
			*random_y = rand() % fieldSize_y;
			if (randomValueGrid[*random_x][*random_y] != 9 && *random_x != field_x && *random_y != field_y)
			{
				randomValueGrid[*random_x][*random_y] = 9;
				numberMines += 1;
				i++;
			}
		}
		break;
	case 1:
		for (int i = 0; i < 25;)
		{
			*random_x = rand() % this->fieldSize_x;
			*random_y = rand() % this->fieldSize_y;
			if (randomValueGrid[*random_x][*random_y] != 9 && *random_x != field_x && *random_y != field_y)
			{
				randomValueGrid[*random_x][*random_y] = 9;
				numberMines += 1;
				i++;
			}
		}
		break;
	case 2:
		for (int i = 0; i < 35;)
		{
			*random_x = rand() % this->fieldSize_x;
			*random_y = rand() % this->fieldSize_y;
			if (randomValueGrid[*random_x][*random_y] != 9 && *random_x != field_x && *random_y != field_y)
			{
				randomValueGrid[*random_x][*random_y] = 9;
				numberMines += 1;
				i++;
			}
		}
		break;
	default:
		break;
	}


	for (int i = 0; i < fieldSize_x; i++)
		for (int j = 0; j < fieldSize_y; j++)
		{
			*temp_gridValue = 0;
			if (randomValueGrid[i][j] == 9) continue;
			if ((i + 1) < fieldSize_x && randomValueGrid[i + 1][j] == 9) *temp_gridValue += 1;
			if ((j + 1) < fieldSize_y && randomValueGrid[i][j + 1] == 9) *temp_gridValue += 1;
			if ((i - 1) >= 0 && randomValueGrid[i - 1][j] == 9)
				*temp_gridValue += 1;
			if ((j - 1) >= 0 && randomValueGrid[i][j - 1] == 9) *temp_gridValue += 1;
			if ((i + 1) < fieldSize_x && (j + 1) < fieldSize_y && randomValueGrid[i + 1][j + 1] == 9) *temp_gridValue += 1;
			if ((i - 1) >= 0 && (j - 1) >= 0 && randomValueGrid[i - 1][j - 1] == 9) *temp_gridValue += 1;
			if ((i - 1) >= 0 && (j + 1) < fieldSize_y && randomValueGrid[i - 1][j + 1] == 9) *temp_gridValue += 1;
			if ((i + 1) < fieldSize_x && (j - 1) >= 0 && randomValueGrid[i + 1][j - 1] == 9) *temp_gridValue += 1;

			randomValueGrid[i][j] = *temp_gridValue;
		}

	delete random_x;
	delete random_y;
	delete temp_gridValue;
	random_x = nullptr;
	random_y = nullptr;
	temp_gridValue = nullptr;
}

void Field::Ride(int field_x, int field_y)
{
	//this->Print_randomValueGrid();
	if (displayGrid[field_x][field_y] != 11)
		displayGrid[field_x][field_y] = randomValueGrid[field_x][field_y];

	if (displayGrid[field_x][field_y] == 9)
	{
		win_or_lose = 2;
		for (int i = 0; i < this->fieldSize_x; i++)
			for (int j = 0; j < this->fieldSize_y; j++)
				displayGrid[i][j] = randomValueGrid[i][j];
	}
	else
		if (displayGrid[field_x][field_y] == 0)
			Empty_square(field_x, field_y);

}

void Field::Empty_square(int field_x, int field_y)
{
	if (randomValueGrid[field_x][field_y] == 0)
	{
		displayGrid[field_x][field_y] = 0;
		if (field_x + 1 > fieldSize_x)
			Empty_square(field_x + 1, field_y);
		if (field_x - 1 < 0)
			Empty_square(field_x - 1, field_y);

		if (field_y + 1 > fieldSize_y)
			Empty_square(field_x, field_y + 1);
		if (field_y - 1 < 0)
			Empty_square(field_x, field_y - 1);
	}
}


void Field::Set_flag(int field_x, int field_y)
{
	if (displayGrid[field_x][field_y] == 11)
	{
		this->numberMines += 1;
		displayGrid[field_x][field_y] = 10;
	}
	else
		if (displayGrid[field_x][field_y] == 10)
		{
			this->numberMines -= 1;
			displayGrid[field_x][field_y] = 11;
		}
}

void Field::CheckWin()
{
	for (int i = 0; i < fieldSize_x; i++)
	{
		for (int j = 0; j < fieldSize_y; j++)
			if (randomValueGrid[i][j] != 9 && displayGrid[i][j] != randomValueGrid[i][j])
			{
				win_or_lose = 0;
				return;
			}
	}
	win_or_lose = 1;
}