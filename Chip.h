#pragma once
#include "SFML/Graphics.hpp"
#include "ClickableObject.h"

class Node;

class Chip : public ClickableObject
{
public:
	Chip();

	void MoveToNode(Node* nodePtr);

	void SetCoordinates(float newX, float newY);

	virtual void Draw(sf::RenderWindow& window) const override;

	void SetChipColor(sf::Color color);

	void SetChipWinPosition(Node* chipsWinNode);

	bool IsInWinPosition()const;

	virtual bool IsClicked(const sf::RenderWindow& window) const override;

	void SetAsSelected(bool IsSelected);

	Node* GetChipsNode() const;

public:
	sf::CircleShape shape;
	sf::CircleShape shape_result;//

private:
	const float radius_ = 20.f;
	sf::Color defaultColor_ = sf::Color::Green;
	sf::Color selectedColor_ = sf::Color::Color(180,180,180);
	Node* chipsNode_ = nullptr;
	Node* chipsWinNode_ = nullptr;
	
};

