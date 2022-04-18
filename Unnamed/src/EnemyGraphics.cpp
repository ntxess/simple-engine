#include "EnemyGraphics.hpp"

EnemyGraphics::EnemyGraphics()
{}

EnemyGraphics::EnemyGraphics(sf::Texture& texture)
{
	_sprite.setTexture(texture);
	_sprite.setScale(sf::Vector2f(2, 2));
	_sprite.setPosition(sf::Vector2f(500.f, 500.f));
}

EnemyGraphics::~EnemyGraphics()
{}

sf::Sprite& EnemyGraphics::GetSprite()
{
	return _sprite;
}

void EnemyGraphics::Render(const std::unique_ptr<sf::RenderWindow>& rw, const float& interpolation)
{
	rw->draw(_sprite);
}
