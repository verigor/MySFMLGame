#include "Chip.h"
#include "Node.h"

Chip::Chip()
{
	shape.setRadius(radius_);
	shape.setOrigin(radius_, radius_);
	shape_result.setRadius(radius_);//
}

void Chip::MoveToNode(Node* nodePtr)
{
	if (chipsNode_)
	{
		chipsNode_->chipPtr = nullptr;
	}
	chipsNode_ = nodePtr;
	nodePtr->chipPtr = this;
}

void Chip::SetCoordinates(float newX, float newY)
{
	shape.setPosition(newX, newY);
}

void Chip::Draw(sf::RenderWindow& window) const
{
	window.draw(shape);
	window.draw(shape_result);
}

void Chip::SetChipColor(sf::Color color)
{
	defaultColor_ = color;
	shape.setFillColor(color);
}

void Chip::SetChipWinPosition(Node* chipsWinNode)
{
	chipsWinNode_ = chipsWinNode;

	shape_result.setPosition(chipsWinNode->GetX()+500, chipsWinNode->GetY()+300);//
	shape_result.setFillColor(defaultColor_);//
}

bool Chip::IsInWinPosition() const
{
	return chipsNode_ == chipsWinNode_;
}

bool Chip::IsClicked(const sf::RenderWindow& window) const
{
	Vector2i position = Mouse::getPosition(window);
	return shape.getGlobalBounds().contains(position.x, position.y);
}

void Chip::SetAsSelected(bool IsSelected)
{
	if (IsSelected)
	{
		//shape.setFillColor(selectedColor);
		shape.setOutlineThickness(10.0f);//
		shape.setOutlineColor(selectedColor_);//
	}
	else
	{
		shape.setFillColor(defaultColor_);
		shape.setOutlineThickness(0.0f);//
	}
}

Node* Chip::GetChipsNode() const
{
	return chipsNode_;
}

