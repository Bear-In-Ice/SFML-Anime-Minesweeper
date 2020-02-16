#pragma once
#include <iterator>
#include <iostream>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "Resources.h"
#include "Field.h"

class State
{
	//Functions 
private:
	virtual void Init() = 0;
	virtual void UpdateSFMLEvents(sf::RenderWindow* target) = 0;
	virtual void Update(sf::RenderWindow* target, Resources& resources) = 0;
	virtual void Render(float& dt, sf::RenderWindow* target, Resources& resources) = 0;

public:
	virtual ~State() {};
	virtual int Run( float& dt, sf::RenderWindow* target,Resources& resources) = 0;
};