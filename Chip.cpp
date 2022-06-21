#include "Chip.h"
#include "Node.h"

Chip::Chip()
{
	shape.setRadius(radius_);
}

void Chip::MoveToNode(Node* nodePtr)
{
	if (chipsNode)
	{
		chipsNode->chipPtr = nullptr;
	}
	chipsNode = nodePtr;
	nodePtr->chipPtr = this;
	shape.setPosition(nodePtr->GetX(), nodePtr->GetY());
}

void Chip::Draw(sf::RenderWindow& window) const
{
	window.draw(shape);
}

void Chip::SetChipColor(sf::Color color)
{
	defaultColor = color;
	shape.setFillColor(color);
}

void Chip::SetChipWinPosition(Node* newWinNode)
{
	chipsWinNode = newWinNode;
}

bool Chip::IsInWinPosition() const
{
	return chipsNode == chipsWinNode;
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
		shape.setFillColor(selectedColor);
	}
	else
	{
		shape.setFillColor(defaultColor);
	}
}

Node* Chip::GetChipsNode() const
{
	return chipsNode;
}

