#include "Engine.hpp"

int main() 
{
    Engine engine(1920, 1080, "Engine 9");
    engine.Run();
    return 0;
}

//#include <iostream>
//#include <math.h>
//#include <SFML/Graphics.hpp>
//
//sf::RenderWindow window;
//
//void GameThread()
//{
//	window.setFramerateLimit(60);
//	sf::Texture sfmlLogo;
//	sfmlLogo.loadFromFile("resources/bg/Space_Stars2.png");
//	sfmlLogo.setSmooth(true);
//
//	sf::Sprite sprLogo;
//	sprLogo.setTexture(sfmlLogo);
//	sprLogo.setOrigin(floor(sfmlLogo.getSize().x / 2.f), floor(sfmlLogo.getSize().y / 2.f));
//	sprLogo.setPosition(400, 300);
//
//	while (window.isOpen())
//	{
//		sprLogo.rotate(0.5f);
//
//		window.clear();
//		window.draw(sprLogo);
//		window.display();
//	}
//}
//
//int main()
//{
//	sf::Thread gameThread(&GameThread);
//	sf::Event event;
//
//	window.create(sf::VideoMode(800, 600, 32), "Test");
//	window.setActive(false);
//
//	gameThread.launch();
//
//	while (window.waitEvent(event))
//	{
//		if (event.type == sf::Event::Closed)
//		{
//			window.close();
//		}
//	}
//
//	gameThread.wait();
//
//	return EXIT_SUCCESS;
//}