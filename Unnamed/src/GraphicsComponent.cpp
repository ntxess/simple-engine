#include "GraphicsComponent.hpp"

GraphicsComponent::GraphicsComponent()
{
	thor::FrameAnimation idle, leftTurn, rightTurn;
	for (int i = 0; i < 4; i++)
		idle.addFrame(1.f, sf::IntRect(16 * i, 0, 16, 24));
	leftTurn.addFrame(1.f, sf::IntRect(0, 0, 16, 24));
	rightTurn.addFrame(1.f, sf::IntRect(64, 0, 16, 24));
	_animator.addAnimation("idle", idle, sf::seconds(1.f));
	_animator.addAnimation("leftTurn", leftTurn, sf::seconds(0.05f));
	_animator.addAnimation("rightTurn", rightTurn, sf::seconds(0.05f));
}

GraphicsComponent::~GraphicsComponent()
{}

void GraphicsComponent::EventReceiver(sf::Vector2f direction)
{
	if (!_animator.isPlayingAnimation())
		_animator.playAnimation("idle");

	if (direction.x > 0)
		_animator.playAnimation("rightTurn");

	if (direction.x < 0)
		_animator.playAnimation("leftTurn");
}

void GraphicsComponent::Update(sf::Sprite& sprite, sf::Vector2f direction, float deltaTime)
{
	EventReceiver(direction);
	_animator.update(sf::seconds(deltaTime));
	_animator.animate(sprite);
}