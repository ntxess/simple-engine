#include "Sprite.hpp"

Sprite::Sprite() 
{}

Sprite::~Sprite()
{}

void Sprite::SetScale(const sf::Vector2f scale)
{
	_sprite.setScale(scale);
}

void Sprite::SetPosition(const sf::Vector2f pos)
{
	_sprite.setPosition(pos);
}

void Sprite::Update(double deltaTime)
{
	if(_animation != nullptr)
		_animation->Update();
}

void Sprite::Render(sf::RenderWindow* rt, double interpolation)
{
	rt->draw(_sprite);
}
