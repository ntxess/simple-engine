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

void Sprite::Update(float deltaTime)
{
	if(_animation != nullptr)
		_animation->Update(deltaTime);
}

void Sprite::Render(RenderWindowRef& rw, float interpolation)
{
	rw->draw(_sprite);
}
