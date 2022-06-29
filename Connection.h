#pragma once
#include"Node.h"
#include<SFML/Graphics.hpp>
#include "DrawableObject.h"


class Connection : public DrawableObject
{
public:
	Connection(Node num1, Node num2);

	virtual void Draw(sf::RenderWindow& window)const override;

public:
	Vertex line[2];
	Vertex line_result[2];

private:
	
};

