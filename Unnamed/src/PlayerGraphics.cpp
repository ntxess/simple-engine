#include "PlayerGraphics.hpp"

PlayerGraphics::PlayerGraphics()
{}

PlayerGraphics::PlayerGraphics(thor::ResourceHolder<sf::Texture, std::string>& holder, std::string ID)
{
	sf::Texture& texture = holder[ID];
	_sprite.setTexture(texture);
	_sprite.setScale(sf::Vector2f(2, 2));
	_sprite.setPosition(sf::Vector2f(360, 900));
	std::cout << "TEXTURE LOADED: " << ID << std::endl;

	thor::FrameAnimation idle, leftTurn, rightTurn;
	idle.addFrame(1.f, sf::IntRect(16, 0, 16, 24));
	leftTurn.addFrame(1.f, sf::IntRect(0, 0, 16, 24));
	rightTurn.addFrame(1.f, sf::IntRect(64, 0, 16, 24));
	_animator.addAnimation("idle", idle, sf::seconds(0.05f));
	_animator.addAnimation("leftTurn", leftTurn, sf::seconds(0.05f));
	_animator.addAnimation("rightTurn", rightTurn, sf::seconds(0.05f));
}

PlayerGraphics::~PlayerGraphics()
{}

sf::Sprite& PlayerGraphics::GetSprite()
{
	return _sprite;
}

void PlayerGraphics::Animator(const GameObject& object)
{
	if (!_animator.isPlayingAnimation())
		_animator.playAnimation("idle");

	if (object.GetInput()->GetDirection().x > 0)
		_animator.playAnimation("rightTurn");

	if (object.GetInput()->GetDirection().x < 0)
		_animator.playAnimation("leftTurn");
}

void PlayerGraphics::Render(const RenderWindowRef& rw, const float& deltaTime, const float& interpolation)
{
	_animator.update(sf::seconds(deltaTime));
	_animator.animate(_sprite);
	rw->draw(_sprite);
}