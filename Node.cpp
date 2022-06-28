#include "Node.h"


Node::Node(int NodeNum) : nodeNum_(NodeNum)
{
}

void Node::Draw(sf::RenderWindow& window) const 
{
	window.draw(shape_);
	window.draw(shape_result);//
}

void Node::SetAsAvailableForChipMoving(bool newAvailable)
{
	if (newAvailable) {
		shape_.setFillColor(availableColor_);
	}
	else
	{
		shape_.setFillColor(defaultColor_);
	}
}

void Node::SetCoordinates(float x, float y)
{
	x_ = x;
	y_ = y;
	shape_.setRadius(radius_);
	shape_.setOrigin(radius_, radius_);
	shape_.setPosition(x_, y_);
	shape_.setFillColor(defaultColor_);

	shape_result.setRadius(radius_);//
	shape_result.setPosition(x_ + 500,y_+300);//
	shape_result.setFillColor(defaultColor_);//
}

bool Node::IsClicked(const sf::RenderWindow& window) const
{
	sf::Vector2i position = sf::Mouse::getPosition(window);
	return shape_.getGlobalBounds().contains(position.x, position.y);
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
	return shape_;
}

float Node::GetX() const
{
	return x_;
}

float Node::GetY() const
{
	return y_;
}

int Node::GetNum() const
{
	return nodeNum_;
}

bool Node::GetWasVisited() const
{
	return wasVisited_;
}

void Node::MarkAsVisited()
{
	wasVisited_ = true;
}

void Node::ClearVisitedState()
{
	wasVisited_ = false;
}
