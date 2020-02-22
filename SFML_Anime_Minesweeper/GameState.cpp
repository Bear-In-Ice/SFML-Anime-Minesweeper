#include "GameState.h"
//Constructors/Destructor
GameState::GameState(Resources& resources, int games_difficulty, int background_number)
{
	font_iterator = resources.LoadFont("images/8bit.ttf");

	this->Init();
	this->games_difficulty = games_difficulty;
	field = new Field(16, 10, resources);

	games_difficulty == 2 ? this->timer_seconds = 210 : 300;
	this->background_number = background_number;
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
	text = new sf::Text("You won!",(*font_iterator).second);
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
						field->Ride(mouse_position_x, mouse_position_y);


			}
			if (event->key.code == sf::Mouse::Right)
				field->Set_flag(mouse_position_x, mouse_position_y);
		}
	}
}

void GameState::UpdateSFMLTime()
{
	this->time = clock->getElapsedTime().asMicroseconds();
	clock->restart();
	time = time / 800;
}

void GameState::Update(sf::RenderWindow* target, Resources& resources)
{
	field->CheckWin();
	this->UpdateSFMLTime();
	*mouse_position = sf::Mouse::getPosition(*target);
	mouse_position_x = ((mouse_position->x - 6.7) / 25) - 5;     //25 - tile width
	mouse_position_y = (mouse_position->y / 25) - 3;		     //25 - tile height

	this->UpdateSFMLEvents(target);
}

void GameState::Render(sf::RenderWindow* target, Resources& resources)
{
	if (field->Get_win_or_lose() == 1)
	{
		target->clear();
		sprite_iterator = resources.LoadSprite("images/bc.png");
		target->draw((*sprite_iterator).second);
		sprite_iterator = resources.LoadSprite("images/pic" + std::to_string(background_number) + ".png");
		sprite_iterator->second.setPosition(((target->getSize().x / 5)), 70);
		target->draw((*sprite_iterator).second);
		text->setPosition(270, 550);
		target->draw(*text);
		target->display();
		return;
	}
	target->clear();
	sprite_iterator = resources.LoadSprite("images/bc.png");
	target->draw((*sprite_iterator).second);
	sprite_iterator = resources.LoadSprite("images/pic" + std::to_string(background_number) + ".png");
	sprite_iterator->second.setPosition(((target->getSize().x / 5)), 70);
	target->draw((*sprite_iterator).second);
	field->Draw_field(target);

	target->display();
		if (field->Get_win_or_lose() == 2)
		{
			int timer = 0;
			this->UpdateSFMLTime();
			for (int i = 1; i < 5;)
			{
				timer += time;
				if (i > 1)
				{
					this->UpdateSFMLTime();
					target->clear();
					sprite_iterator = resources.LoadSprite("images/bc.png");
					target->draw((*sprite_iterator).second);
					sprite_iterator = resources.LoadSprite("images/pic" + std::to_string(background_number) + ".png");
					sprite_iterator->second.setPosition(((target->getSize().x / 5)), 70);
					target->draw((*sprite_iterator).second);
					field->Draw_field(target);
				}
				sprite_iterator = resources.LoadSprite("images/mg" + std::to_string(i) + ".png");
				sprite_iterator->second.setPosition(((target->getSize().x / 4)), 475);
				target->draw((*sprite_iterator).second);
				target->display();
				if (timer > 800)
				{
					i++;
					timer = 0;
				}
			}
			flag_state = 0;
			return;
		}
}


int GameState::Run(sf::RenderWindow* target, Resources& resources)
{
	while (flag_state)
	{
		this->Update(target, resources);
		this->Render(target, resources);
	}
	return flag_state;
}