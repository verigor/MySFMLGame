#include<SFML/Graphics.hpp>
#include"Node.h"
#include"Connection.h"
#include"Chip.h"
#include "GameMap.h"

using namespace sf;

int main()
{

	sf::RenderWindow window(sf::VideoMode(1000, 800), "Cupboards");
	
	GameMapFileReader mapFileReader;
	GameMap gameMap = mapFileReader.ReadGameMapFromFile("input_level1.txt");

	Font font;
	font.loadFromFile("CyrilicOld.TTF");

	Text text("Выигрышное положение", font, 20);
	text.setFillColor(Color::Red);
	text.setStyle(Text::Bold | Text::Underlined);
	text.setPosition(600, 350);


	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || event.type==Event::KeyPressed)
				window.close();

 			gameMap.ProcessEvent(event, window);
		}


		window.clear(sf::Color::Color(100, 149, 237));


		if (gameMap.CheckGameWin())
		{
			Text text("Вы выиграли!", font, 30);
			text.setFillColor(Color::Red);
			text.setStyle(Text::Bold | Text::Underlined);
			text.setPosition(100, 100);
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