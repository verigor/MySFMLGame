#pragma once
#include<SFML/Graphics.hpp>
#include "ClickableObject.h"

class Chip;

using namespace sf;

class Node : public ClickableObject
{
public:
	Node(int newNodeNum);

	void SetAsAvailableForChipMoving( bool newAvailable);

	void SetCoordinates(int x, int y);

	virtual bool IsClicked(const sf::RenderWindow& window) const override;

	virtual void Draw(sf::RenderWindow& window)const override;

	float GetRadius();

	bool HasChip() const;

	const sf::CircleShape& GetShape();

	int GetX() const;

	int GetY() const;

	int GetNum() const;

	bool WasVisited() const;
	void MarkAsVisited();
	void ClearVisitedState();
public:

	Chip* chipPtr = nullptr;

private:
	int x_;
	int y_;
	float radius_ = 15.f;
	sf::CircleShape shape;
	sf::Color defaultColor= sf::Color::Red;
	sf::Color availableColor = sf::Color::White;

	const int nodeNum = -1;

	bool wasVisited = false;
};

