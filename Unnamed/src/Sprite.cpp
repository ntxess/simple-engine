#include "Sprite.hpp"

Sprite::Sprite()
{}

Sprite::Sprite(thor::ResourceHolder<sf::Texture, std::string>& holder, std::string ID) : _animationName("flying")
{
	sf::Texture& texure = holder[ID];
	_sprite.setTexture(texure);
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

void Sprite::SetScale(const sf::Vector2f scale)
{
	_sprite.setScale(scale);
}

void Sprite::SetPosition(const sf::Vector2f pos)
{
	_sprite.setPosition(pos);
}

void Sprite::Move(sf::Vector2f direction, int velocity, float deltaTime)
{
	float x = direction.x * velocity * deltaTime;
	float y = direction.y * velocity * deltaTime;
	_sprite.move(x, y);
}

void Sprite::Update(float deltaTime)
{}

void Sprite::Update(sf::Vector2f direction, int velocity, float deltaTime)
{
	Move(direction, velocity, deltaTime);
	if (!_animator.isPlayingAnimation())
		_animator.playAnimation(_animationName);
	_animator.update(sf::seconds(deltaTime));
	_animator.animate(_sprite);
}

void Sprite::Render(RenderWindowRef& rw, float interpolation)
{
	rw->draw(_sprite);
}