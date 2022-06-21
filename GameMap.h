#pragma once
#include "SFML/Graphics.hpp"
#include <vector>
#include "Node.h"

class GameMap;

class GameMapFileReader {


public:

	GameMap ReadGameMapFromFile(const std::string& fileName);

};

class GameMap {


public:

	GameMap(int numberOfChips, int numberOfNodes);

	void AddConnection(int firstNode, int secondNode);

	bool HasConnection(int firstNode, int secondNode) const;

	bool HasChip(int nodeNumber) const;

	void SetChipPosition(int chipNumber, int nodeNumber);

	void SetChipPosition(Chip* chip, Node* node);

	void SetChipWinPosition(int chipNumber, int nodeNumber);

	void SetChipWinPosition(Chip* chip, Node* node);

	void DrawGameMap(sf::RenderWindow& window);

	void ProcessEvent(const sf::Event& event, const sf::RenderWindow& window);

private:

	void SelectChip(const sf::RenderWindow& window);

	void SelectChipDestination(const sf::RenderWindow& window);

	void UpdateAvailablePaths(Chip* chip);

	void FindNearestAvailableNodes(Node* node);

	void MarkAllNodesAsUnvisited();

	bool IsSomeChipSelected() const;

	void ClearChipSelection();

	bool CheckGameWin() const;

	void OnGameWin();

	const sf::Color& GetAvailableChipColor(int chipNum) const;

public:

	std::vector<Node> nodes;

	std::vector<Chip> chips;

private:

	int nodesNum = 0;

	int chipsNum = 0;

	std::vector<std::vector<bool>> nodeConnectionsGraph;

	Chip* selectedChip = nullptr;

	std::vector<Node*> availableNodesToMoveChip;
};

