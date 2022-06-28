#include "GameMap.h"
#include <fstream>
#include "Connection.h"
#include "Chip.h"

GameMap::GameMap(int chipsNum, int nodesNum)
{
	chipsNum_ = chipsNum;
	nodesNum_ = nodesNum;

	//инициализировали граф соединений нулями
	for (int i = 0; i < nodesNum; i++)
	{
		std::vector<bool> connectionRow;
		for (int q = 0; q < nodesNum; q++)
		{
			connectionRow.push_back(0);
		}
		nodeConnectionsGraph_.push_back(connectionRow);
	}

	//создали массив узловых точек
	for (int i = 0; i < nodesNum; i++)
	{
		nodes.push_back(Node(i));
	}

	//создали массив фишек
	for (int i = 0; i < chipsNum; i++) 
	{
		Chip newChip;
		//каждой фишке свой цвет
		newChip.SetChipColor(GetAvailableChipColor(i));
		chips.push_back(newChip);
	}
}

// заполнили граф соединений
void GameMap::AddConnection(int firstNode, int secondNode)
{
	nodeConnectionsGraph_[firstNode][secondNode] = 1;
	nodeConnectionsGraph_[secondNode][firstNode] = 1;
}

bool GameMap::HasConnection(int firstNode, int secondNode) const
{
	return nodeConnectionsGraph_[firstNode][secondNode] == 1;
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
	if (chip->IsInWinPosition()) 
	{
		if (CheckGameWin()) 
		{
			OutputMessageWin();
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
			SetChipPosition(selectedChip_, currentNode);
			return;
		}
	}
}

void GameMap::UpdateAvailablePaths(Chip* chip)
{
	Node* chipsNode = chip->GetChipsNode();
	availableNodesToMoveChip_.clear();
	MarkAllNodesAsUnvisited();
	FindNearestAvailableNodes(chipsNode);
}

void GameMap::FindNearestAvailableNodes(Node* node)
{
	node->MarkAsVisited();
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
				FindNearestAvailableNodes(&nodes[nodeToCheck]);
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

bool GameMap::IsSomeChipSelected() const
{
	return selectedChip_ != nullptr;
}

void GameMap::ClearChipSelection()
{
	selectedChip_->SetAsSelected(false);
	selectedChip_ = nullptr;
	availableNodesToMoveChip_.clear();
}

bool GameMap::CheckGameWin() const
{
	for (const Chip& currentChip : chips) 
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


const sf::Color& GameMap::GetAvailableChipColor(int chipNum) const
{
	sf::Color availableColors[6] = { sf::Color::Color(138, 43, 226), 
									 sf::Color::Green, 
									 sf::Color::Blue, 
									 sf::Color::Cyan, 
		                             sf::Color::Magenta, 
		                             sf::Color::Yellow };
	const int resultColorNum = chipNum % 6;

	return availableColors[resultColorNum];
}

GameMap GameMapFileReader::ReadGameMapFromFile(const std::string& fileName)
{
	std::fstream inputFile(fileName);
	
	int chipsNum=0;
	int nodesNum=0;

	//считываем из файла количество фишек
	inputFile >> chipsNum;
	// cчитываем из файла количество узловых точек, куда можно поместить фишку
	inputFile >> nodesNum;

	GameMap resultGameMap(chipsNum, nodesNum);

	//cчитываем из файла координаты для узловых точек
	for (int i = 0; i < nodesNum; i++) 
	{
		float nodeXPos;
		float nodeYPos;
		inputFile >> nodeXPos;
		inputFile >> nodeYPos;
		resultGameMap.nodes[i].SetCoordinates(nodeXPos, nodeYPos);
	}

	//cчитываем из файла начальное расположение фишек по точкам 
	for (int i = 0; i < chipsNum; i++) 
	{
		int chipStartPosition;
		inputFile >> chipStartPosition;
		chipStartPosition--;
		resultGameMap.SetChipPosition(i, chipStartPosition);
	}

	//cчитываем из файла выигрышное положение фишек по точкам
	for (int i = 0; i < chipsNum; i++) 
	{
		int chipEndPosition;
		inputFile >> chipEndPosition;
		chipEndPosition--;
		resultGameMap.SetChipWinPosition(i, chipEndPosition);
	}

	//cчитываем из файла количество соединений
	int numConnections;
	inputFile >> numConnections;

	//cчитываем из файла список соединений между парами точек
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

