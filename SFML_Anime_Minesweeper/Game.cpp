#include "Game.h"
//Constructor/Destructors
Game::Game()
{
	this->InitWindow();
}

Game::~Game()
{
	delete state;
	state = nullptr;
}


//Initialization
void Game::InitWindow() //initializes window
{
	this->window.create(sf::VideoMode(this->window_width, this->window_height), "Minesweeper", sf::Style::Titlebar);   //sf::Style::Titlebar:  Title bar + fixed border
}

//Function
void Game::Run()
{
	gameStates = GameStates::STATE_MENU;
	while (this->window.isOpen())
	{
		switch (gameStates)
		{
		case GameStates::STATE_MENU:
		{
			this->state = new MenuState(this->resources);
			if (this->state->Run( &window, this->resources) == 2)
			{
				delete state;
				gameStates = GameStates::STATE_LEVEL;
			}
			else
				if (this->state->Run( &window, this->resources) == 0)
					this->window.close();			
		}
		break;
		case GameStates::STATE_LEVEL:
		{
			this->state = new LevelState(this->resources);
			if (this->state->Run( &window, this->resources) == 0)
			{
				delete state;
				gameStates = GameStates::STATE_MENU;
			}
			else
				if (this->state->Run( &window, this->resources) == 1)
				{
					lvl = this->state->Get_lvl();
					delete state;
					gameStates = GameStates::STATE_GAME;
					this->games_difficulty = 0;
				}	
				else
					if (this->state->Run(&window, this->resources) == 2)
					{
						lvl = this->state->Get_lvl();
						delete state;
						gameStates = GameStates::STATE_GAME;
						this->games_difficulty = 1;
					}
		}
			break;
		case GameStates::STATE_GAME:
		{
			this->state = new GameState(this->resources,this->games_difficulty, lvl);
			if (this->state->Run(&window, this->resources) == 0)
			{
				delete state;
				gameStates = GameStates::STATE_MENU;
			}
			else
				if (this->state->Run( &window, this->resources) == 1)
					this->window.close();
		}
		break;
		default:
			break;
		}
	}
}
