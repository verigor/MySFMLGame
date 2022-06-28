#pragma once
#include "SFML/Graphics.hpp"
#include <vector>
#include "Node.h"

class GameMap;

class GameMapFileReader
{
public:
	GameMap ReadGameMapFromFile(const std::string& fileName);

};


class GameMap 
{
public:
	GameMap(int chipsNum, int nodesNum);

	void AddConnection(int firstNode, int secondNode);

	bool HasConnection(int firstNode, int secondNode) const;

	bool HasChip(int nodeNumber) const;

	void SetChipPosition(int chipNumber, int nodeNumber);

	void SetChipPosition(Chip* chip, Node* node, bool MoveNodeSmoothly = false);

	std::vector<Node*> GetChipWay(Node* destinationNode) const;

	void SetChipWinPosition(int chipNumber, int nodeNumber);

	void SetChipWinPosition(Chip* chip, Node* node);

	void DrawGameMap(sf::RenderWindow& window);

	void ProcessEvent(const sf::Event& event, const sf::RenderWindow& window);

	bool CheckGameWin() const;//public

public:
	std::vector<Node> nodes;
	std::vector<Chip> chips;

private:
	void SelectChip(const sf::RenderWindow& window);

	void SelectChipDestination(const sf::RenderWindow& window);

	void UpdateAvailablePaths(Chip* chip);

	void FindNearestAvailableNodes(Node* node, Node* previousNode);

	void MarkAllNodesAsUnvisited();

	bool IsSomeChipSelected() const;

	void ClearChipSelection();

	void OutputMessageWin();

	const sf::Color& GetAvailableChipColor(int chipNum) const;

	bool IsChipMoving() const;

	void UpdateChipPosition();

private:
	int nodesNum_ = 0;
	int chipsNum_ = 0;
	std::vector<std::vector<bool>> nodeConnectionsGraph_;
	Chip* selectedChip_ = nullptr;
	std::vector<Node*> availableNodesToMoveChip_;

	Chip* movingChip = nullptr;
	std::vector<Node*> chipMovingWay;

	const int movingSpeed = 1;
};

