#pragma once
#include<SFML/Graphics.hpp>
#include "ClickableObject.h"

class Chip;

using namespace sf;

class Node : public ClickableObject
{
public:
	Node(int NodeNum);

	void SetAsAvailableForChipMoving(bool newAvailable);

	void SetCoordinates(float x, float y);

	virtual bool IsClicked(const sf::RenderWindow& window) const override;

	virtual void Draw(sf::RenderWindow& window)const override;

	bool HasChip() const;

	float GetRadius();

	const sf::CircleShape& GetShape();

	float GetX() const;

	float GetY() const;

	int GetNum() const;

	bool GetWasVisited() const;

	Node* GetPreviousVisitedNode() const;

	void MarkAsVisited(Node* nodeVisitedFrom);

	void ClearVisitedState();

public:
	Chip* chipPtr = nullptr;

private:
	const int nodeNum_ = -1;
	float x_ = 0;
	float y_ = 0;
	const float radius_ = 12.f;
	bool wasVisited_ = false;
	Node* backwardsWayPtr = nullptr;
	sf::CircleShape shape_;
	sf::CircleShape shape_result;//
	sf::Color defaultColor_ = sf::Color::Red;
	sf::Color availableColor_ = sf::Color::White;

};

