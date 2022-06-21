#include<SFML/Graphics.hpp>
#include"Player.h"
#include"Map.h"
#include"Node.h"
#include"Connection.h"
#include"Chip.h"
#include "GameMap.h"

using namespace sf;


int main()
{

	sf::RenderWindow window(sf::VideoMode(800, 600), "My window");

	GameMapFileReader mapFileReader;
	GameMap gameMap = mapFileReader.ReadGameMapFromFile("input.txt");

	// run the program as long as the window is open
	while (window.isOpen())
	{
		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (window.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
				window.close();

			gameMap.ProcessEvent(event, window);
		}

		window.clear(sf::Color::Black);

		gameMap.DrawGameMap(window);

		window.display();
	}

	return 0;



	//sf::RenderWindow window(sf::VideoMode(1200, 900), "process");

	//float x1 = 100, y1 = 100;
	//float x2 = 200, y2 = 100;
	//float x3 = 300, y3 = 100;
	//float x4 = 100, y4 = 200;
	//float x5 = 200, y5 = 200;
	//float x6 = 300, y6 = 200;
	//float x7 = 100, y7 = 300;
	//float x8 = 200, y8 = 300;
	//float x9 = 300, y9 = 300;


	//Player pl("hero.png", 96, 0, 96, 96);
	//

	//Node node1(x1, y1);
	//Node node2(x2, y2);
	//Node node3(x3, y3);
	//Node node4(x4, y4);
	//Node node5(x5, y5);
	//Node node6(x6, y6);
	//Node node7(x7, y7);
	//Node node8(x8, y8);
	//Node node9(x9, y9);

	//Chip chip1(node1);

	//Connection connect1(node1, node4);
	///*Connection connect2(node2, node5);
	//Connection connect3(node3, node6);
	//Connection connect4(node4, node5);
	//Connection connect5(node5, node6);
	//Connection connect6(node4, node7);
	//Connection connect7(node5, node8);
	//Connection connect8(node6, node9);*/

	//Vertex line1[] = {
	//	Vertex(Vector2f(x1 + node1.GetRadius(), y1 + node1.GetRadius())),
	//	Vertex(Vector2f(x4 + node4.GetRadius(), y4 + node4.GetRadius()))
	//};
	//line1->color = Color::Black;

	//Vertex line2[] = {
	//	Vertex(Vector2f(x2 + node2.GetRadius(), y2 + node2.GetRadius())),
	//	Vertex(Vector2f(x5 + node5.GetRadius(), y5 + node5.GetRadius()))
	//};
	//line2->color = Color::Black;

	//Vertex line3[] = {
	//	Vertex(Vector2f(x3 + node3.GetRadius(), y3 + node3.GetRadius())),
	//	Vertex(Vector2f(x6 + node6.GetRadius(), y6 + node6.GetRadius()))
	//};
	//line3->color = Color::Black;

	//Vertex line4[] = {
	//	Vertex(Vector2f(x4 + node4.GetRadius(), y4 + node4.GetRadius())),
	//	Vertex(Vector2f(x5 + node5.GetRadius(), y5 + node5.GetRadius()))
	//};
	//line4->color = Color::Black;

	//Vertex line5[] = {
	//	Vertex(Vector2f(x5 + node5.GetRadius(), y5 + node5.GetRadius())),
	//	Vertex(Vector2f(x6 + node6.GetRadius(), y6 + node6.GetRadius()))
	//};
	//line5->color = Color::Black;

	//Vertex line6[] = {
	//	Vertex(Vector2f(x4 + node4.GetRadius(), y4 + node4.GetRadius())),
	//	Vertex(Vector2f(x7 + node7.GetRadius(), y7 + node7.GetRadius()))
	//};
	//line6->color = Color::Black;

	//Vertex line7[] = {
	//	Vertex(Vector2f(x5 + node5.GetRadius(), y5 + node5.GetRadius())),
	//	Vertex(Vector2f(x8 + node8.GetRadius(), y8 + node8.GetRadius()))
	//};
	//line7->color = Color::Black;

	//Vertex line8[] = {
	//	Vertex(Vector2f(x6 + node6.GetRadius(), y6 + node6.GetRadius())),
	//	Vertex(Vector2f(x9 + node9.GetRadius(), y9 + node9.GetRadius()))
	//};
	//line8->color = Color::Black;


	//Image map_image;
	//map_image.loadFromFile("images/map.png");
	//Texture texture;
	//texture.loadFromImage(map_image);
	//Sprite s_map;
	//s_map.setTexture(texture);

	//float currentFrame = 0;
	//Clock clock;

	//bool isMove = false;
	//bool isSelect = false;
	//float dX = 0;
	//float dY = 0;
	//int tempX = 0;
	//int tempY = 0;
	//float distance = 0;

	//while (window.isOpen())
	//{
	//	float time = clock.getElapsedTime().asMicroseconds();

	//	clock.restart();
	//	time /= 1000;

	//	Vector2i position = Mouse::getPosition(window);

	//	sf::Event event;
	//	while (window.pollEvent(event))
	//	{
	//		if (event.type == sf::Event::Closed)
	//			window.close();



	//		if (event.type == Event::MouseButtonPressed)
	//		{
	//			if (event.key.code == Mouse::Left)
	//			{
	//				if (chip1.shape.getGlobalBounds().contains(position.x, position.y))
	//				{
	//					//isMove = true;
	//					chip1.shape.setFillColor(Color::Black);
	//					isSelect = true;
	//				}


	//				//if (pl.sprite.getGlobalBounds().contains(position.x, position.y))
	//				//{
	//				//	/*dX = position.x - pl.sprite.getPosition().x;
	//				//	dY = position.y - pl.sprite.getPosition().y;*/
	//				//	//isMove = true;
	//				//	pl.sprite.setColor(Color::Black);
	//				//	isSelect = true;
	//				//}
	//			}
	//		}
	//	}
	//	/*if (event.type == Event::MouseButtonReleased)
	//	{
	//		if (event.key.code == Mouse::Left)
	//		{
	//			isMove = false;
	//			pl.sprite.setColor(Color::White);
	//		}
	//	}*/


	//	if (isSelect)
	//	{
	//		if (event.type == Event::MouseButtonPressed)
	//		{
	//			if (event.key.code == Mouse::Right)
	//			{
	//				isMove = true;
	//				isSelect = false;
	//				//chip1.shape.setFillColor(Color::Green);
	//				tempX = position.x;
	//				tempY = position.y;
	//			}
	//		}
	//	}


	//	if (isMove)
	//	{
	//		distance = sqrt((tempX - chip1.x_) * (tempX - chip1.x_) + (tempY - chip1.y_) * (tempY - chip1.y_));
	//		if (distance > 2)
	//		{
	//			chip1.x_ += 0.1 * time * (tempX - chip1.x_) / distance;
	//			chip1.y_ += 0.1 * time * (tempY - chip1.y_) / distance;
	//		}


	//	/*pl.x = position.x - dX;
	//	pl.y = position.y - dY;*/
	//	distance = sqrt((tempX - pl.x) * (tempX - pl.x) + (tempY - pl.y) * (tempY - pl.y));
	//	if (distance > 2)
	//		{
	//			pl.x += 0.1 * time * (tempX - pl.x) / distance;
	//			pl.y += 0.1 * time * (tempY - pl.y) / distance;
	//		}
	//	}



	//	if (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A))
	//	{
	//		chip1.direction = 1;
	//		chip1.speed = 0.1;
	//		
	//		pl.directn = 1;
	//		pl.speed = 0.1;
	//		currentFrame += time * 0.005;
	//		if (currentFrame > 3) { currentFrame -= 3; }
	//		pl.sprite.setTextureRect(IntRect(96 * int(currentFrame), 96, 96, 96));
	//		pl.sprite.setColor(Color::Magenta);
	//	}
	//	if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D))
	//	{
	//		chip1.direction = 0;
	//		chip1.speed = 0.1;

	//		pl.directn = 0;
	//		pl.speed = 0.1;
	//		currentFrame += time * 0.005;
	//		if (currentFrame > 3) { currentFrame -= 3; }
	//		pl.sprite.setTextureRect(IntRect(96 * int(currentFrame), 192, 96, 96));
	//		pl.sprite.setColor(Color::Green);
	//	}
	//	if (Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::W))
	//	{
	//		chip1.direction = 3;
	//		chip1.speed = 0.1;

	//		pl.directn = 3;
	//		pl.speed = 0.1;
	//		currentFrame += time * 0.005;
	//		if (currentFrame > 3) { currentFrame -= 3; }
	//		pl.sprite.setTextureRect(IntRect(96 * int(currentFrame), 288, 96, 96));
	//		pl.sprite.setColor(Color::Blue);
	//	}
	//	if (Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::S))
	//	{
	//		chip1.direction = 2;
	//		chip1.speed = 0.1;

	//		pl.directn = 2;
	//		pl.speed = 0.1;
	//		currentFrame += time * 0.005;
	//		if (currentFrame > 3) { currentFrame -= 3; }
	//		pl.sprite.setTextureRect(IntRect(96 * int(currentFrame), 0, 96, 96));
	//		pl.sprite.setColor(Color::Yellow);
	//	}

	//	/*if (Mouse::isButtonPressed(Mouse::Left))
	//	{
	//		pl.sprite.setColor(Color::Cyan);
	//	}
	//	if (Mouse::isButtonPressed(Mouse::Right))
	//	{
	//		pl.sprite.setColor(Color::White);
	//	}*/

	//	pl.update(time);
	//	//chip1.update(time);

	//	window.clear();

	//	for (size_t i = 0; i < HEIGHT_MAP; i++)
	//	{
	//		for (size_t j = 0; j < WIDTH_MAP; j++)
	//		{
	//			if (TileMap[i][j] == ' ')
	//			{
	//				s_map.setTextureRect(IntRect(0, 0, 32, 32));
	//			}
	//			if (TileMap[i][j] == 's')
	//			{
	//				s_map.setTextureRect(IntRect(32, 0, 32, 32));
	//			}
	//			if (TileMap[i][j] == '0')
	//			{
	//				s_map.setTextureRect(IntRect(64, 0, 32, 32));
	//			}
	//			s_map.setPosition(j * 32, i * 32);
	//			window.draw(s_map);
	//		}
	//	}
	//	/*window.draw(pl.sprite);
	//	window.draw(node1.shape);
	//	window.draw(node2.shape);
	//	window.draw(node3.shape);
	//	window.draw(node4.shape);
	//	window.draw(node5.shape);
	//	window.draw(node6.shape);
	//	window.draw(node7.shape);
	//	window.draw(node8.shape);
	//	window.draw(node9.shape);

	//	window.draw(chip1.shape);*/
	//	window.draw (connect1.line, 2, Lines);
	//	/*window.draw(line1, 2, Lines);
	//	window.draw(line2, 2, Lines);
	//	window.draw(line3, 2, Lines);
	//	window.draw(line4, 2, Lines);
	//	window.draw(line5, 2, Lines);
	//	window.draw(line6, 2, Lines);
	//	window.draw(line7, 2, Lines);
	//	window.draw(line8, 2, Lines);*/



//}
	//	window.display();
	


//	return 0;
}