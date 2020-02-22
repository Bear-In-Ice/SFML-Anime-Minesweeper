#pragma once
#include "State.h"

class LevelState
	:public State
{
private:
	//Variables
	int flag_state;
	int lvl;
	float mouse_position_x;
	float mouse_position_y;

	sf::Event* event;
	sf::Vector2i* mouse_position;


	//SFML Sprite and Texture
	std::map<std::string, sf::Sprite>::iterator sprite_iterator;

	//Functions 
	void Init() override;
	void UpdateSFMLEvents(sf::RenderWindow* target) override;
	void Update(sf::RenderWindow* target, Resources& resources) override;
	void Render( sf::RenderWindow* target, Resources& resources) override;

public:
	//Constructors/Destructor
	LevelState(Resources& resources);
	 ~LevelState();

	int Run(sf::RenderWindow* target, Resources& resources) override;
	int Get_lvl() { return lvl; };
};
