#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "Resources.h" 
#include "Field.h" 

class Game
{
private:
	//SFML elements
	sf::RenderWindow window;
	sf::Clock clock;
	sf::Event event;

	const int window_width = 700;
	const int window_height = 800;
	const float dt = 1.0f / 60.0f;


	Resources resources;
	Field field{ 10,10,this->resources };

public:

	//Constructor
	Game();

	//Initialization
	void initWindow();		//initializes window

	//Functions 
	void updateSFMLEvents();
	void update();
	void render();
	void run();
};