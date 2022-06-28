#pragma once
#include "DrawableObject.h"

class ClickableObject : public DrawableObject
{
public:
	virtual bool IsClicked(const sf::RenderWindow& window) const = 0;

};

