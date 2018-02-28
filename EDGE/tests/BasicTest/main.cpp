#include "stdafx.h"

#include <EDGE/Everything.hpp>

int main()
{
	sf::RenderWindow window{ {800, 600}, "OpenGL Window" };

	while (window.isOpen())
	{
		sf::Event windowEvent;
		while (window.pollEvent(windowEvent))
		{
			if (windowEvent.type == sf::Event::Closed)
				window.close();
		}


		window.clear();

		window.display();
	}
}

