#include "Game.h"
//Constructor/Destructors
Game::Game()
{
	this->initWindow();
}


//Initialization
void Game::initWindow() //initializes window
{
	this->window.create(sf::VideoMode(this->window_width, this->window_height), "Minesweeper!", sf::Style::Titlebar);   //sf::Style::Titlebar:  Title bar + fixed border
}

//Functions 
void Game::updateSFMLEvents()
{
	while (this->window.pollEvent(this->event))
	{
		if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))
			this->window.close();

		if (event.type == sf::Event::Closed)
			this->window.close();

		if (event.type == sf::Event::MouseButtonPressed)
		{

		}
	}
}

void Game::update()
{
	this->updateSFMLEvents();
}

void Game::render()
{
	this->window.clear();
	field.draw_field(window);
	this->window.display();
}
void Game::run()
{
	while (this->window.isOpen())
	{
		this->update();
		this->render();
	}
}
