#include "MusicNote.hpp"

MusicNote::MusicNote() 
{
	Init();
}

MusicNote::~MusicNote() 
{}

void MusicNote::Init()
{
	if (!_texture.loadFromFile("resources/sp/p1.png"))
	{
		std::cout << "FAILURE TO LOAD SPRITE TEXTURE!" << std::endl;
		exit(-1);
	}
	_sprite.setTexture(_texture);
	_sprite.setScale(sf::Vector2f(1, 1));
	std::cout << "TEXTURE LOADED: " << "resources/bg/bg_fld_1.png" << std::endl;
}
