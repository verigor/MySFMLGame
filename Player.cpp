#include "Player.h"

Player::Player(sf::String f, int X, int Y, float W, float H)
{
	file = f;
	w = W;
	h = H;
	image.loadFromFile("images/" + file);
	image.createMaskFromColor(sf::Color(41, 33, 59));
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	x = X;
	y = Y;
	sprite.setTextureRect(sf::IntRect(x, y, w, h));
}

void Player::update(float time)
{
	switch (directn)
	{
	case 0:
	{
		dx = speed;
		dy = 0;
		break;
	}
	case 1:
	{
		dx = -speed;
		dy = 0;
		break;
	}
	case 2:
	{
		dx = 0;
		dy = speed;
		break;
	}
	case 3:
	{
		dx = 0;
		dy = -speed;
		break;
	}
	default:
		break;
	}

	x += dx * time;
	y += dy * time;
	speed = 0;
	sprite.setPosition(x, y);
}
