#include "PlayerGraphics.hpp"

PlayerGraphics::PlayerGraphics()
{}

PlayerGraphics::PlayerGraphics(thor::ResourceHolder<sf::Texture, std::string>& holder, const std::string& ID)
{
	sf::Texture& texture = holder[ID];
	_sprite.setTexture(texture);
	_sprite.setScale(sf::Vector2f(2, 2));
	_sprite.setPosition(sf::Vector2f(360, 900));
	std::cout << "TEXTURE LOADED: " << ID << std::endl;

}

PlayerGraphics::~PlayerGraphics()
{}

sf::Sprite& PlayerGraphics::GetSprite()
{
	return _sprite;
}

void PlayerGraphics::Animator(const GameObject& object)
{
	//if (!_animator.isPlayingAnimation())
	//	_animator.playAnimation("idle");

	//if (object.GetInput()->GetDirection().x > 0)
	//	_animator.playAnimation("rightTurn");

	//if (object.GetInput()->GetDirection().x < 0)
	//	_animator.playAnimation("leftTurn");
}

void PlayerGraphics::Render(const RenderWindowRef& rw, const float& interpolation)
{
	rw->draw(_sprite);
}