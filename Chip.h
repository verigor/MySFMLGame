#pragma once
#include "SFML/Graphics.hpp"
#include "ClickableObject.h"

class Node;

class Chip : public ClickableObject
{
public:
	Chip();

	sf::CircleShape shape;

	void MoveToNode(Node* nodePtr);

	virtual void Draw(sf::RenderWindow& window) const override;

	void SetChipColor(sf::Color color);

	void SetChipWinPosition(Node* newWinNode);

	bool IsInWinPosition()const;

	virtual bool IsClicked(const sf::RenderWindow& window) const override;

	void SetAsSelected(bool IsSelected);

	Node* GetChipsNode() const;

private:
	float radius_ = 20.f;
	sf::Color defaultColor = sf::Color::Green;
	sf::Color selectedColor = sf::Color::Black;

	Node* chipsNode = nullptr;

	Node* chipsWinNode = nullptr;
	
};

