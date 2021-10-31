#include "Background.hpp"

Background::Background()
{
	Init();
}

Background::~Background()
{}

void Background::Init()
{
	sf::Texture texture;
	if (!texture.loadFromFile("resources/bg/bg1.png"))
	{
		std::cout << "FAILURE TO LOAD SPRITE TEXTURE!" << std::endl;
		exit(-1);
	}
	_sprite.setTexture(texture);
	_sprite.setScale(sf::Vector2f(1, 1));
	std::cout << "TEXTURE LOADED: " << "resources/bg/bg1.png" << std::endl;
}
