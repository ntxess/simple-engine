#include "Sprite.hpp"

Sprite::Sprite() 
{}

Sprite::Sprite(std::string location)
{
	if (!_texture.loadFromFile(location))
	{
		std::cout << "FAILURE TO LOAD SPRITE TEXTURE!" << std::endl;
		exit(-1);
	}
	_sprite.setTexture(_texture);
	_sprite.setScale(sf::Vector2f(1, 1));
	std::cout << "TEXTURE LOADED: " << location << std::endl;
}
Sprite::~Sprite()
{}

sf::Sprite Sprite::GetSprite() const
{
	return _sprite;
}

void Sprite::SetScale(const sf::Vector2f scale)
{
	_sprite.setScale(scale);
}

void Sprite::SetPosition(const sf::Vector2f pos)
{
	_sprite.setPosition(pos);
}

void Sprite::Update(float deltaTime)
{
	if(_animation != nullptr)
		_animation->Update(deltaTime);
}

void Sprite::Render(RenderWindowRef& rw, float interpolation)
{
	rw->draw(_sprite);
}
