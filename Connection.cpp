#include "Connection.h"


Connection::Connection(Node num1, Node num2)
{
	line[0] = Vertex(Vector2f(num1.GetX(), num1.GetY() ));
	line[1] = Vertex(Vector2f(num2.GetX(), num2.GetY() ));
	line[0].color = Color::White;
	line[1].color = Color::White;

	line_result[0] = Vertex(Vector2f(num1.GetX()+500, num1.GetY()+300 ));
	line_result[1] = Vertex(Vector2f(num2.GetX()+500 , num2.GetY()+300 ));
	line_result[0].color = Color::White;
	line_result[1].color = Color::White;
}

void Connection::Draw(sf::RenderWindow& window) const
{
	window.draw(line, 2, Lines);
	window.draw(line_result, 2, Lines);
}
