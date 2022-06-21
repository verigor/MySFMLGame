#include "Node.h"


Node::Node(int newNodeNum) : nodeNum(newNodeNum)
{
}

void Node::Draw(sf::RenderWindow& window) const 
{
	window.draw(shape);
}

void Node::SetAsAvailableForChipMoving(bool newAvailable)
{
	if (newAvailable) {
		shape.setFillColor(availableColor);
	}
	else
	{
		shape.setFillColor(defaultColor);
	}
	
}

void Node::SetCoordinates(int x, int y)
{
	x_ = x;
	y_ = y;
	shape.setRadius(radius_);
	shape.setPosition(x_, y_);
	//shape.setFillColor(sf::Color::Red);
	shape.setFillColor(defaultColor);
}

bool Node::IsClicked(const sf::RenderWindow& window) const
{
	Vector2i position = Mouse::getPosition(window);
	return shape.getGlobalBounds().contains(position.x, position.y);
}

float Node::GetRadius()
{
	return radius_;
}

bool Node::HasChip() const
{
	return chipPtr != nullptr;
}

const sf::CircleShape& Node::GetShape()
{
	return shape;
}

int Node::GetX() const
{
	return x_;
}

int Node::GetY() const
{
	return y_;
}

int Node::GetNum() const
{
	return nodeNum;
}

bool Node::WasVisited() const
{
	return wasVisited;
}

void Node::MarkAsVisited()
{
	wasVisited = true;
}

void Node::ClearVisitedState()
{
	wasVisited = false;
}
