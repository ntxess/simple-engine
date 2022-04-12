#include "EnemyGraphics.hpp"

EnemyGraphics::EnemyGraphics()
{}

EnemyGraphics::EnemyGraphics(thor::ResourceHolder<sf::Texture, std::string>& holder, const std::string& ID)
{
	sf::Texture& texture = holder[ID];
	_sprite.setTexture(texture);
	_sprite.setScale(sf::Vector2f(2, 2));
	_sprite.setPosition(sf::Vector2f(500.f, 500.f));
	std::cout << "TEXTURE LOADED: " << ID << std::endl;
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
