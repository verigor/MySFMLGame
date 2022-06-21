#include "GameMap.h"
#include <fstream>
#include "Connection.h"
#include "Chip.h"

GameMap::GameMap(int numberOfChips, int numberOfNodes)
{
	nodesNum = numberOfNodes;
	chipsNum = numberOfChips;

	for (int i = 0; i < numberOfNodes; i++) {
		std::vector<bool> connectionRow;
		for (int q = 0; q < numberOfNodes; q++) {
			connectionRow.push_back(0);
		}
		nodeConnectionsGraph.push_back(connectionRow);
	}

	for (int i = 0; i < numberOfNodes; i++) {
		nodes.push_back(Node(i));
	}

	for (int i = 0; i < numberOfChips; i++) {
		Chip newChip;
		newChip.SetChipColor(GetAvailableChipColor(i));
		chips.push_back(newChip);
	}
}

void GameMap::AddConnection(int firstNode, int secondNode)
{
	nodeConnectionsGraph[firstNode][secondNode] = 1;
	nodeConnectionsGraph[secondNode][firstNode] = 1;
}

bool GameMap::HasConnection(int firstNode, int secondNode) const
{
	return nodeConnectionsGraph[firstNode][secondNode] == 1;
}

bool GameMap::HasChip(int nodeNumber) const
{
	return nodes[nodeNumber].HasChip();
}

void GameMap::SetChipPosition(int chipNumber, int nodeNumber)
{
	SetChipPosition(&chips[chipNumber], &nodes[nodeNumber]);
}

void GameMap::SetChipPosition(Chip* chip, Node* node)
{
	chip->MoveToNode(node);
	if (chip->IsInWinPosition()) {
		if (CheckGameWin()) {
			OnGameWin();
		}
	}
}

void GameMap::SetChipWinPosition(int chipNumber, int nodeNumber)
{
	SetChipWinPosition(&chips[chipNumber], &nodes[nodeNumber]);
}

void GameMap::SetChipWinPosition(Chip* chip, Node* node)
{
	chip->SetChipWinPosition(node);
}

void GameMap::DrawGameMap(sf::RenderWindow& window)
{
	for (int i = 0; i < nodesNum; i++) {
		nodes[i].Draw(window);
		nodes[i].SetAsAvailableForChipMoving(false);
	}

	for (Node* currentNodePtr : availableNodesToMoveChip) {
		currentNodePtr->SetAsAvailableForChipMoving(true);
	}

	for (int i = 0; i < nodesNum; i++) {
		for (int q = 0; q < i; q++) {

			if (HasConnection(i, q)) {

				Connection connection(nodes[i], nodes[q]);
				connection.Draw(window);
			}

		}
	}

	for (Chip& currentChip : chips) {
		currentChip.Draw(window);
	}
}

void GameMap::ProcessEvent(const sf::Event& event, const sf::RenderWindow& window)
{
	if (event.type != Event::MouseButtonPressed) {
		return;
	}

	if (event.key.code != Mouse::Left) {
		return;
	}

	if (!IsSomeChipSelected()) {
		SelectChip(window);
		return;
	}

	SelectChipDestination(window);
	ClearChipSelection();

}

void GameMap::SelectChip(const sf::RenderWindow& window)
{
	for (Chip& currentChip : chips) {

		if (currentChip.IsClicked(window)) {
			selectedChip = &currentChip;
			selectedChip->SetAsSelected(true);
			UpdateAvailablePaths(&currentChip);
			return;
		}

	}
}

void GameMap::SelectChipDestination(const sf::RenderWindow& window)
{
	for (Node* currentNode : availableNodesToMoveChip) {

		if (currentNode->IsClicked(window)) {
			SetChipPosition(selectedChip, currentNode);
			return;
		}

	}
}

void GameMap::UpdateAvailablePaths(Chip* chip)
{
	Node* chipsNode = chip->GetChipsNode();
	availableNodesToMoveChip.clear();
	MarkAllNodesAsUnvisited();
	FindNearestAvailableNodes(chipsNode);
}

void GameMap::FindNearestAvailableNodes(Node* node)
{
	node->MarkAsVisited();
	const int nodeNumber = node->GetNum();
	for (int nodeToCheck = 0; nodeToCheck < nodesNum; nodeToCheck++) {

		if (nodes[nodeToCheck].WasVisited()) {
			continue;
		}

		if (HasConnection(nodeNumber, nodeToCheck)) {
			if (!HasChip(nodeToCheck)) {
				availableNodesToMoveChip.push_back(&nodes[nodeToCheck]);
				FindNearestAvailableNodes(&nodes[nodeToCheck]);
			}
		}

	}
}

void GameMap::MarkAllNodesAsUnvisited()
{
	for (Node& currentNode : nodes) {
		currentNode.ClearVisitedState();
	}
}

bool GameMap::IsSomeChipSelected() const
{
	return selectedChip != nullptr;
}

void GameMap::ClearChipSelection()
{
	selectedChip->SetAsSelected(false);
	selectedChip = nullptr;
	availableNodesToMoveChip.clear();
}

bool GameMap::CheckGameWin() const
{
	for (const Chip& currentChip : chips) {
		if (!currentChip.IsInWinPosition()) {
			return false;
		}
	}

	return true;
}

void GameMap::OnGameWin()
{
	int a = 10;
	a--;
}

const sf::Color& GameMap::GetAvailableChipColor(int chipNum) const
{
	sf::Color availableColors[6] = { sf::Color::White, sf::Color::Green, sf::Color::Blue, sf::Color::Cyan, sf::Color::Magenta, sf::Color::Yellow };
	const int resultColorNum = chipNum % 6;
	return availableColors[resultColorNum];
}

GameMap GameMapFileReader::ReadGameMapFromFile(const std::string& fileName)
{
	std::fstream inputFile(fileName);
	
	int chipsNum;
	int nodesNum;

	inputFile >> chipsNum;
	inputFile >> nodesNum;

	GameMap resultGameMap(chipsNum, nodesNum);

	for (int i = 0; i < nodesNum; i++) {
		int nodeXPos;
		int nodeYPos;
		inputFile >> nodeXPos;
		inputFile >> nodeYPos;

		resultGameMap.nodes[i].SetCoordinates(nodeXPos, nodeYPos);
	}

	for (int i = 0; i < chipsNum; i++) {
		int chipStartPosition;
		inputFile >> chipStartPosition;
		chipStartPosition--;
		resultGameMap.SetChipPosition(i, chipStartPosition);
	}

	for (int i = 0; i < chipsNum; i++) {
		int chipEndPosition;
		inputFile >> chipEndPosition;
		chipEndPosition--;
		resultGameMap.SetChipWinPosition(i, chipEndPosition);
	}

	int numConnections;
	inputFile >> numConnections;

	for (int i = 0; i < numConnections; i++) {
		int firstNode;
		int secondNode;
		inputFile >> firstNode;
		inputFile >> secondNode;
		firstNode--;
		secondNode--;
		resultGameMap.AddConnection(firstNode, secondNode);
	}
	return resultGameMap;
}
