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

	bool HasConnection(int firstNode, int secondNode) ;

	bool HasChip(int nodeNumber) ;

	void SetChipPosition(int chipNumber, int nodeNumber);

	void SetChipPosition(Chip* chip, Node* node, bool MoveNodeSmoothly = false);

	std::vector<Node*> GetChipWay(Node* destinationNode) ;

	void SetChipWinPosition(int chipNumber, int nodeNumber);

	void SetChipWinPosition(Chip* chip, Node* node);

	void DrawGameMap(sf::RenderWindow& window);

	void ProcessEvent(const sf::Event& event, const sf::RenderWindow& window);

	bool CheckGameWin() ;

public:
	std::vector<Node> nodes;
	std::vector<Chip> chips;

private:
	void SelectChip(const sf::RenderWindow& window);

	void SelectChipDestination(const sf::RenderWindow& window);

	void UpdateAvailablePaths(Chip* chip);

	void FindNearestAvailableNodes(Node* node, Node* previousNode);

	void MarkAllNodesAsUnvisited();

	bool IsSomeChipSelected() ;

	void ClearChipSelection();

	void OutputMessageWin();

	const sf::Color& GetAvailableChipColor(int chipNum) ;

	bool IsChipMoving() ;

	void UpdateChipPosition();

private:
	int nodesNum_;
	int chipsNum_ ;
	std::vector<std::vector<bool>> nodeConnectionsGraph_;
	Chip* selectedChip_ = nullptr;
	std::vector<Node*> availableNodesToMoveChip_;

	Chip* movingChip_ = nullptr;
	std::vector<Node*> chipMovingWay_;

	const int movingSpeed_ = 1;
};

