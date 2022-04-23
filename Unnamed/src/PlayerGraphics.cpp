#include "PlayerGraphics.hpp"

PlayerGraphics::PlayerGraphics()
{}

PlayerGraphics::PlayerGraphics(sf::Texture& texture)
{
	_sprite.setTexture(texture);
	_sprite.setScale(sf::Vector2f(1, 1));
	_sprite.setPosition(sf::Vector2f(360, 900));
}

PlayerGraphics::~PlayerGraphics()
{}

sf::Sprite& PlayerGraphics::GetSprite()
{
	return _sprite;
}

void PlayerGraphics::Render(const std::unique_ptr<sf::RenderWindow>& rw, const float& interpolation)
{
	rw->draw(_sprite);
}