#include "Sprite.hpp"

Sprite::Sprite() 
{}

Sprite::~Sprite()
{}

thor::Animator<sf::Sprite, std::string>& Sprite::GetAnimator()
{
	return _animator;
}

void Sprite::EventReceiver(sf::Vector2f direction)
{
	if (!_animator.isPlayingAnimation())
		_animator.playAnimation("idle");

	if (direction.x > 0)
		_animator.playAnimation("rightTurn");

	if (direction.x < 0)
		_animator.playAnimation("leftTurn");
}

void Sprite::Update(sf::Vector2f direction, float deltaTime)
{
	EventReceiver(direction);
	_animator.update(sf::seconds(deltaTime));
}