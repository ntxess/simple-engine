#include "PlayerGraphics.hpp"

PlayerGraphics::PlayerGraphics()
{}

PlayerGraphics::PlayerGraphics(thor::ResourceHolder<sf::Texture, std::string>& holder, const std::string& ID)
{
	sf::Texture& texture = holder[ID];
	_sprite.setTexture(texture);
	_sprite.setScale(sf::Vector2f(2, 2));
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