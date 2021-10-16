#include "MusicNote.hpp"

MusicNote::MusicNote() 
{
	Init();
}

MusicNote::~MusicNote() {}

void MusicNote::Init()
{
	if (!_texture.loadFromFile("resources/bg/bg_fld_1.png"))
	{
		std::cout << "FAILURE TO LOAD SPRITE TEXTURE!" << std::endl;
		exit(-1);
	}
	//_animation = Animation(&_texture, imageCount, switchTime, delay);
	_sprite.setTexture(_texture);
	//_sprite.setTextureRect(_animation._uvRect);
	_sprite.setScale(sf::Vector2f(0.2,0.2));
	std::cout << "TEXTURE LOADED: " << "resources/bg/bg_fld_1.png" << std::endl;
}
