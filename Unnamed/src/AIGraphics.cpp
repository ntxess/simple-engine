#include "AIGraphics.hpp"

AIGraphics::AIGraphics()
{}

AIGraphics::AIGraphics(thor::ResourceHolder<sf::Texture, std::string>& holder, std::string ID)
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

AIGraphics::~AIGraphics()
{}
sf::Sprite& AIGraphics::GetSprite()
{
	return _sprite;
}

void AIGraphics::Animator(const GameObject& object)
{
	sf::Vector2f direction = object.GetInput()->GetDirection();
	if (!_animator.isPlayingAnimation())
		_animator.playAnimation("idle");

	if (direction.x > 0)
		_animator.playAnimation("rightTurn");

	if (direction.x < 0)
		_animator.playAnimation("leftTurn");
}

void AIGraphics::Render(const RenderWindowRef& rw, const float& deltaTime, const float& interpolation)
{
	_animator.update(sf::seconds(deltaTime));
	_animator.animate(_sprite);
	rw->draw(_sprite);
}
