#include "GameMap.h"
#include <fstream>
#include "Connection.h"
#include "Chip.h"

GameMap::GameMap(int chipsNum, int nodesNum)
{
	chipsNum_ = chipsNum;
	nodesNum_ = nodesNum;

	for (int i = 0; i < nodesNum; i++)
	{
		std::vector<bool> connectionRow;
		for (int q = 0; q < nodesNum; q++)
		{
			connectionRow.push_back(0);
		}
		nodeConnectionsGraph_.push_back(connectionRow);
	}

	for (int i = 0; i < nodesNum; i++)
	{
		nodes.push_back(Node(i));
	}

	for (int i = 0; i < chipsNum; i++) 
	{
		Chip newChip;
		newChip.SetChipColor(GetAvailableChipColor(i));
		chips.push_back(newChip);
	}
}

void GameMap::AddConnection(int firstNode, int secondNode)
{
	nodeConnectionsGraph_[firstNode][secondNode] = 1;
	nodeConnectionsGraph_[secondNode][firstNode] = 1;
}

bool GameMap::HasConnection(int firstNode, int secondNode) 
{
	return nodeConnectionsGraph_[firstNode][secondNode] == 1;
}

bool GameMap::HasChip(int nodeNumber) 
{
	return nodes[nodeNumber].HasChip();
}

void GameMap::SetChipPosition(int chipNumber, int nodeNumber)
{
	SetChipPosition(&chips[chipNumber], &nodes[nodeNumber]);
}

void GameMap::SetChipPosition(Chip* chip, Node* node, bool MoveNodeSmoothly)
{
	chip->MoveToNode(node);
	if (MoveNodeSmoothly)
	{
		movingChip_ = chip;
		chipMovingWay_.clear();
		chipMovingWay_ = GetChipWay(node);
	}
	else
	{
		chip->SetCoordinates(node->GetX(), node->GetY());
	}

	if (chip->IsInWinPosition()) 
	{
		if (CheckGameWin()) 
		{
			OutputMessageWin();
		}
	}
}

std::vector<Node*> GameMap::GetChipWay(Node* destinationNode) 
{
	std::vector<Node*> resultWay;
	Node* currentNode = destinationNode;
	while (currentNode != nullptr)
	{
		if (currentNode->GetPreviousVisitedNode() == nullptr) 
		{
			break;
		}

		resultWay.push_back(currentNode);
		currentNode = currentNode->GetPreviousVisitedNode();
	}

	std::reverse(resultWay.begin(), resultWay.end());
	return resultWay;
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
	for (int i = 0; i < nodesNum_; i++)
	{
		nodes[i].Draw(window);
		nodes[i].SetAsAvailableForChipMoving(false);
	}

	for (Node* currentNodePtr : availableNodesToMoveChip_) 
	{
		currentNodePtr->SetAsAvailableForChipMoving(true);
	}

	for (int i = 0; i < nodesNum_; i++)
	{
		for (int q = 0; q < i; q++)
		{
			if (HasConnection(i, q))
			{
				Connection connection(nodes[i], nodes[q]);
				connection.Draw(window);
			}
		}
	}

	for (Chip& currentChip : chips)
	{
		currentChip.Draw(window);
	}

	UpdateChipPosition();
}

void GameMap::ProcessEvent(const sf::Event& event, const sf::RenderWindow& window)
{
	if (event.type != Event::MouseButtonPressed)
	{
		return;
	}

	if (event.key.code != Mouse::Left)
	{
		return;
	}

	if (IsChipMoving()) 
	{
		return;
	}

	if (!IsSomeChipSelected())
	{
		SelectChip(window);
		return;
	}

	SelectChipDestination(window);
	ClearChipSelection();
}

void GameMap::SelectChip(const sf::RenderWindow& window)
{
	for (Chip& currentChip : chips) 
	{
		if (currentChip.IsClicked(window)) 
		{
			selectedChip_ = &currentChip;
			selectedChip_->SetAsSelected(true);
			UpdateAvailablePaths(&currentChip);
			return;
		}
	}
}

void GameMap::SelectChipDestination(const sf::RenderWindow& window)
{
	for (Node* currentNode : availableNodesToMoveChip_) 
	{
		if (currentNode->IsClicked(window)) 
		{
			SetChipPosition(selectedChip_, currentNode, true);
			return;
		}
	}
}

void GameMap::UpdateAvailablePaths(Chip* chip)
{
	Node* chipsNode = chip->GetChipsNode();
	availableNodesToMoveChip_.clear();
	MarkAllNodesAsUnvisited();
	FindNearestAvailableNodes(chipsNode, nullptr);
}

void GameMap::FindNearestAvailableNodes(Node* node, Node* previousNode)
{
	node->MarkAsVisited(previousNode);
	const int nodeNumber = node->GetNum();
	for (int nodeToCheck = 0; nodeToCheck < nodesNum_; nodeToCheck++) 
	{
		if (nodes[nodeToCheck].GetWasVisited()) 
		{
			continue;
		}

		if (HasConnection(nodeNumber, nodeToCheck)) 
		{
			if (!HasChip(nodeToCheck)) 
			{
				availableNodesToMoveChip_.push_back(&nodes[nodeToCheck]);
				FindNearestAvailableNodes(&nodes[nodeToCheck], node);
			}
		}
	}
}

void GameMap::MarkAllNodesAsUnvisited()
{
	for (Node& currentNode : nodes) 
	{
		currentNode.ClearVisitedState();
	}
}

bool GameMap::IsSomeChipSelected() 
{
	return selectedChip_ != nullptr;
}

void GameMap::ClearChipSelection()
{
	selectedChip_->SetAsSelected(false);
	selectedChip_ = nullptr;
	availableNodesToMoveChip_.clear();
}

bool GameMap::CheckGameWin()
{
	for ( Chip& currentChip : chips) 
	{
		if (!currentChip.IsInWinPosition()) 
		{
			return false;
		}
	}

	return true;
}

void GameMap::OutputMessageWin()
{
}


const sf::Color& GameMap::GetAvailableChipColor(int chipNum) 
{
	sf::Color availableColors[6] = { sf::Color::Color(138, 43, 226), 
									 sf::Color::Green, 
									 sf::Color::Blue, 
									 sf::Color::Cyan, 
		                             sf::Color::Magenta, 
		                             sf::Color::Yellow };
	int resultColorNum = chipNum % 6;

	return availableColors[resultColorNum];
}

bool GameMap::IsChipMoving() 
{
	return !chipMovingWay_.empty();
}

void GameMap::UpdateChipPosition()
{
	if (!IsChipMoving()) 
	{
		return;
	}

	if (movingChip_ == nullptr) 
	{
		return;
	}

	Node* destinationNode = chipMovingWay_[0];

	const float currentChipX = movingChip_->shape.getPosition().x;
	float xMovingDirection = destinationNode->GetX() > currentChipX ? 1.f : -1.f;
	float newChipX = currentChipX + movingSpeed_ * xMovingDirection;

	const float currentChipY = movingChip_->shape.getPosition().y;
	float yMovingDirection = destinationNode->GetY() > currentChipY ? 1.f : -1.f;
	float newChipY = currentChipY + movingSpeed_ * yMovingDirection;

	movingChip_->SetCoordinates(newChipX, newChipY);

	const float distanceError = 1.f;
	if (std::fabsf(destinationNode->GetX() - newChipX) < distanceError &&
		std::fabsf(destinationNode->GetY() - newChipY) < distanceError)
	{
		chipMovingWay_.erase(chipMovingWay_.begin());
	}
}

GameMap GameMapFileReader::ReadGameMapFromFile(const std::string& fileName)
{
	std::fstream inputFile(fileName);
	
	int chipsNum=0;
	int nodesNum=0;

	inputFile >> chipsNum;
	inputFile >> nodesNum;

	GameMap resultGameMap(chipsNum, nodesNum);

	for (int i = 0; i < nodesNum; i++) 
	{
		float nodeXPos;
		float nodeYPos;
		inputFile >> nodeXPos;
		inputFile >> nodeYPos;
		resultGameMap.nodes[i].SetCoordinates(nodeXPos, nodeYPos);
	}

	for (int i = 0; i < chipsNum; i++) 
	{
		int chipStartPosition;
		inputFile >> chipStartPosition;
		chipStartPosition--;
		resultGameMap.SetChipPosition(i, chipStartPosition);
	}

	for (int i = 0; i < chipsNum; i++) 
	{
		int chipEndPosition;
		inputFile >> chipEndPosition;
		chipEndPosition--;
		resultGameMap.SetChipWinPosition(i, chipEndPosition);
	}

	int numConnections;
	inputFile >> numConnections;

	for (int i = 0; i < numConnections; i++) 
	{
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