#pragma once
#include"Node.h"
#include<SFML/Graphics.hpp>
#include "DrawableObject.h"

class Connection : public DrawableObject
{
public:

	Vertex line[2];
	Connection(Node num1, Node num2)
	{
		line[0] = Vertex(Vector2f(num1.GetX() + num1.GetRadius(), num1.GetY() + num1.GetRadius()));
		line[1] = Vertex(Vector2f(num2.GetX() + num2.GetRadius(), num2.GetY() + num2.GetRadius()));
		line[0].color = Color::White;
		line[1].color = Color::White;
	}

	virtual void Draw(sf::RenderWindow& window)const override;
	
	

private:
	
};

