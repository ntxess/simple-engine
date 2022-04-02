#include "PlayerGraphics.hpp"

PlayerGraphics::PlayerGraphics()
{
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

void PlayerGraphics::Animator(Player& player)
{
	if (!_animator.isPlayingAnimation())
		_animator.playAnimation("idle");

	if (player._input->_direction.x > 0)
		_animator.playAnimation("rightTurn");

	if (player._input->_direction.x < 0)
		_animator.playAnimation("leftTurn");
}

void PlayerGraphics::Render(RenderWindowRef& rw, float deltaTime, float interpolation)
{
	_animator.update(sf::seconds(deltaTime));
	_animator.animate(_sprite);
	rw->draw(_sprite);
}
