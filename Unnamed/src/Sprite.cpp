#include "Sprite.hpp"

Sprite::Sprite() 
	: _isAnimated(false)
{}

Sprite::Sprite(thor::ResourceHolder<sf::Texture, std::string>& holder, std::string ID, bool isAnimated) : _isAnimated(isAnimated)
{
	sf::Texture& texture = holder[ID];
	_sprite.setTexture(texture);
	_sprite.setScale(sf::Vector2f(1, 1));
	std::cout << "TEXTURE LOADED: " << ID << std::endl;
}

Sprite::~Sprite()
{}

sf::Sprite& Sprite::GetSprite()
{
	return _sprite;
}

thor::Animator<sf::Sprite, std::string>& Sprite::GetAnimator()
{
	return _animator;
}

void Sprite::Move(sf::Vector2f direction, float velocity, float deltaTime)
{
	float x = direction.x * velocity * deltaTime;
	float y = direction.y * velocity * deltaTime;
	_sprite.move(x, y);
}

void Sprite::Update(float deltaTime)
{
	if (_isAnimated)
	{
		if (!_animator.isPlayingAnimation())
			_animator.playAnimation("idle");
		_animator.update(sf::seconds(deltaTime));
		_animator.animate(_sprite);
	}
}

void Sprite::Update(sf::Vector2f direction, float velocity, float deltaTime)
{
	Move(direction, velocity, deltaTime);

	if (_isAnimated)
	{
		if (!_animator.isPlayingAnimation())
			_animator.playAnimation("idle");
		_animator.update(sf::seconds(deltaTime));
		_animator.animate(_sprite);
	}
}

void Sprite::Render(RenderWindowRef& rw, float interpolation)
{
	rw->draw(_sprite);
}