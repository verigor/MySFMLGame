#include "Connection.h"

void Connection::Draw(sf::RenderWindow& window) const
{
	window.draw(line, 2, Lines);
}
