#include "MenuState.h"
//Constructors/Destructor
MenuState::MenuState(Resources& resources)
{
	this->Init();
	sprite_iterator = resources.LoadSprite("images/bc1.png");
}

MenuState::~MenuState()
{
	delete event;
	delete mouse_position;
	event = nullptr;
	mouse_position = nullptr;
}

//Functions 
void MenuState::Init()
{
	event = new sf::Event;
	mouse_position = new sf::Vector2i;

	this->flag_state = 1;
}

void MenuState::UpdateSFMLEvents(sf::RenderWindow* target)
{
	while (target->pollEvent(*event))
	{
		if ((event->type == sf::Event::KeyPressed) && (event->key.code == sf::Keyboard::Escape))
			flag_state = 0;
		if (event->type == sf::Event::MouseButtonPressed )
			if (event->key.code == sf::Mouse::Left)
			{
				if (mouse_position_x > 1.64 && mouse_position_x < 2.64 && mouse_position_y >7.5 && mouse_position_y < 8.5)
					flag_state = 2;
				if (mouse_position_x > 1.64 && mouse_position_x < 2.64 && mouse_position_y >9.1 && mouse_position_y < 10.1)
					flag_state = 0;
			}
	}
}

void MenuState::Update(sf::RenderWindow* target, Resources& resources)
{
	*mouse_position = sf::Mouse::getPosition(*target);
	mouse_position_x = ((float)mouse_position->x / 194); //194 - button width
	mouse_position_y = ((float)mouse_position->y / 65);	 //65 - button height

	/*system("cls");
	std::cout << mouse_position_x << "||" << mouse_position_y;*/

	if (mouse_position_x > 1.64 && mouse_position_x < 2.64 && mouse_position_y >7.5 && mouse_position_y < 8.5)
		sprite_iterator = resources.LoadSprite("images/bc2.png");
	else
		if (mouse_position_x > 1.64 && mouse_position_x < 2.64 && mouse_position_y >9.1 && mouse_position_y < 10.1)
			sprite_iterator = resources.LoadSprite("images/bc3.png");
		else
			sprite_iterator = resources.LoadSprite("images/bc1.png");

	this->UpdateSFMLEvents(target);

}

void MenuState::Render(sf::RenderWindow* target, Resources& resources)
{
	target->clear();
	target->draw((*sprite_iterator).second);
	target->display();
}


int MenuState::Run(sf::RenderWindow* target, Resources& resources)
{
	while (flag_state==1)
	{
		this->Update(target, resources);
		this->Render(target, resources);
	}
	return flag_state;
}