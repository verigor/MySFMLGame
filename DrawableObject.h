#pragma once
#include "SFML/Graphics.hpp"

class DrawableObject
{
public:
	virtual void Draw(sf::RenderWindow& window) const = 0;

};

