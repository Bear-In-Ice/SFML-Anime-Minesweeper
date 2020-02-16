#include "GameState.h"
//Constructors/Destructor
GameState::GameState(Resources& resources, int games_difficulty)
{
	this->Init();
	this->games_difficulty = games_difficulty;
	field = new Field(16, 10, resources);

	games_difficulty == 2 ? this->timer_seconds = 210 : 300;
}

GameState::~GameState()
{
	delete event;
	delete clock;
	delete mouse_position;
	delete field;
	event = nullptr;
	clock = nullptr;
	mouse_position = nullptr;
	field = nullptr;
}

//Functions 
void GameState::Init()
{
	event = new sf::Event;
	clock = new sf::Clock;
	mouse_position = new sf::Vector2i;

	this->flag_state = 1;
	this->first_ride = 1;
	this->time = 0;
}

void GameState::UpdateSFMLEvents(sf::RenderWindow* target)
{
	while (target->pollEvent(*event))
	{
		if ((event->type == sf::Event::KeyPressed) && (event->key.code == sf::Keyboard::Escape))
			flag_state = 0;
		if (event->type == sf::Event::MouseButtonPressed)
		{
			if (event->key.code == sf::Mouse::Left)
			{
				if (mouse_position_x >= 0 && mouse_position_x < field->Get_fieldSize_x() && mouse_position_y >= 0 && mouse_position_y < field->Get_fieldSize_y() && this->first_ride == 1)
				{
					this->first_ride = 0;
					field->Fill_randomValueGrid(mouse_position_x, mouse_position_y, games_difficulty);
					field->Ride(mouse_position_x, mouse_position_y);

				}
				else
					if (mouse_position_x >= 0 && mouse_position_x < field->Get_fieldSize_x() && mouse_position_y >= 0 && mouse_position_y < field->Get_fieldSize_y())
					{
						field->Ride(mouse_position_x, mouse_position_y);
						system("cls");
						field->Print_randomValueGrid();
						field->Print_displayGrid();
					}
			}
			if (event->key.code == sf::Mouse::Right)
				if (this->first_ride != 1)
					field->Set_flag(mouse_position_x, mouse_position_y);
		}
	}
}

void GameState::Update(sf::RenderWindow* target, Resources& resources)
{
	*mouse_position = sf::Mouse::getPosition(*target);
	mouse_position_x = ((mouse_position->x - 6.7) / 25) - 5;     //25 - tile width
	mouse_position_y = (mouse_position->y / 25) - 3;		    //25 - tile height

	this->UpdateSFMLEvents(target);

}

void GameState::Render(float& dt, sf::RenderWindow* target, Resources& resources)
{
	target->clear();
	sprite_iterator = resources.LoadSprite("images/bc.png");
	target->draw((*sprite_iterator).second);
	sprite_iterator = resources.LoadSprite("images/pik1.png");
	sprite_iterator->second.setPosition(((target->getSize().x / 5)), 70);
	target->draw((*sprite_iterator).second);
	field->Draw_field(target);
	target->display();
}


int GameState::Run(float& dt, sf::RenderWindow* target, Resources& resources)
{
	while (flag_state)
	{
		this->Update(target, resources);
		this->Render(dt, target, resources);
	}
	return flag_state;
}