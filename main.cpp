#include<SFML/Graphics.hpp>
#include"Node.h"
#include"Connection.h"
#include"Chip.h"
#include "GameMap.h"

using namespace sf;
//const int SHIFT_X = 500;

int main()
{

	sf::RenderWindow window(sf::VideoMode(1000, 800), "Cupboards");
	window.setFramerateLimit(60);//
	
	GameMapFileReader mapFileReader;
	GameMap gameMap = mapFileReader.ReadGameMapFromFile("input_level1.txt");


	Font font;//
	font.loadFromFile("CyrilicOld.TTF");//

	Text text("Выигрышное положение", font, 20);//
	text.setFillColor(Color::Red);//
	text.setStyle(Text::Bold | Text::Underlined);//
	text.setPosition(600, 350);//

	

	float rad = 10.0f;
	CircleShape fig(rad);
	fig.setFillColor(Color::Color(199, 21, 133));
	fig.setOrigin(rad,rad);
	Vector2f figPosition(0, 0);
	float x = 100;
	float y = 600;
	Vector2f figPositionEnd(x, y);
	float xVelocity = x / 100;
	float yVelocity = y / 100;
	Vertex line_e[2];
	line_e[0] = Vertex(Vector2f(figPosition));
	line_e[1] = Vertex(Vector2f(figPositionEnd));
	line_e[0].color = Color::White;
	line_e[1].color = Color::White;




	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || event.type==Event::KeyPressed)
				window.close();

			gameMap.ProcessEvent(event, window);
		}



		if (figPosition.x>figPositionEnd.x)
		{
			xVelocity *= 0;
		}
		if ( figPosition.y>figPositionEnd.y)
		{
			yVelocity *= 0;
		}
		figPosition.x += xVelocity;
		figPosition.y += yVelocity;
		fig.setPosition(figPosition);


		


		window.clear(sf::Color::Color(100, 149, 237));


		


		//gameMap.DrawGameMap(window);

		//
		window.draw(fig);
		window.draw(line_e, 2, Lines);

		if (gameMap.CheckGameWin())
		{
			Text text("Вы выиграли!", font, 30);//
			text.setFillColor(Color::Red);//
			text.setStyle(Text::Bold | Text::Underlined);//
			text.setPosition(100, 100);//
			window.draw(text);
		}
		else
		{
			gameMap.DrawGameMap(window);
			window.draw(text);
		}



		window.display();
	}

	return 0;
}