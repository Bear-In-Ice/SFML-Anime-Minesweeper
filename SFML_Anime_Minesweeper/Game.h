#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "Resources.h" 
#include "MenuState.h"
#include "LevelState.h"
#include "GameState.h"

enum class GameStates
{
	STATE_MENU = 0,
	STATE_LEVEL = 1,
	STATE_GAME = 2,
	STATE_ENDGAME = 3
};

class Game
{
private:
	//SFML elements
	sf::RenderWindow window;
	sf::Clock clock;
	sf::Event event;
	State* state;

	const int window_width = 700;
	const int window_height = 800;
	float dt = 1.0f / 60.0f;   //Delta time


	int games_difficulty;  // 0 - easy || 1 - medium || 2 - hard

	GameStates gameStates;

	Resources resources;

	//Initialization
	void InitWindow();		//initializes window
public:

	//Constructors/Destructor
	Game();
	~Game();

	//Function 
	void Run();
};