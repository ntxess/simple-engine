#include "Sprite.hpp"

Sprite::Sprite() : _animation(nullptr) 
{}

Sprite::~Sprite()
{
	delete _animation;
}

void Sprite::SetScale(const sf::Vector2f scale)
{
	_sprite.setScale(scale);
}

void Sprite::SetPosition(const sf::Vector2f pos)
{
	_sprite.setPosition(pos);
	_posN = pos;
}

void Sprite::Update()
{
	if(_animation != nullptr)
		_animation->Update();
}

void Sprite::Render(sf::RenderTarget* rt, double interpolation)
{
	rt->draw(_sprite);
}
