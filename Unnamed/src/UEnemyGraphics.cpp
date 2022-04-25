#include "UEnemyGraphics.hpp"

UEnemyGraphics::UEnemyGraphics()
{}

UEnemyGraphics::UEnemyGraphics(sf::Texture& texture)
{
	_sprite.setTexture(texture);
	_sprite.setScale(sf::Vector2f(2, 2));
	_sprite.setOrigin(float(texture.getSize().x / 2), float(texture.getSize().y / 2));
	_sprite.setPosition(sf::Vector2f(500.f, 500.f));
}

UEnemyGraphics::~UEnemyGraphics()
{}

sf::Sprite& UEnemyGraphics::GetSprite()
{
	return _sprite;
}

void UEnemyGraphics::Render(const std::unique_ptr<sf::RenderWindow>& rw, const float& interpolation)
{
	rw->draw(_sprite);
}
