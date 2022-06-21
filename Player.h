#pragma once
#include <SFML/Graphics.hpp>

class Player
{
public:
	float x, y, w, h, dx, dy, speed = 0;
	int directn = 0;
	sf::String file;
	sf::Image image;
	sf::Texture texture;
	sf::Sprite sprite;
	

	Player(sf::String f, int X, int Y, float W, float H);
	void update(float time);
	
private:

};

