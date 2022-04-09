#include "AIGraphics.hpp"

AIGraphics::AIGraphics()
{}

AIGraphics::AIGraphics(thor::ResourceHolder<sf::Texture, std::string>& holder, const std::string& ID)
{
	sf::Texture& texture = holder[ID];
	_sprite.setTexture(texture);
	_sprite.setScale(sf::Vector2f(2, 2));
	_sprite.setPosition(sf::Vector2f(360, 900));
	std::cout << "TEXTURE LOADED: " << ID << std::endl;
}

AIGraphics::~AIGraphics()
{}
sf::Sprite& AIGraphics::GetSprite()
{
	return _sprite;
}

void AIGraphics::Animator(const GameObject& object)
{}

void AIGraphics::Render(const RenderWindowRef& rw, const float& interpolation)
{
	rw->draw(_sprite);
}
