#include "Sprite.hpp"

Sprite::Sprite()
{}

Sprite::Sprite(thor::ResourceHolder<sf::Texture, std::string>& holder, std::string ID)
{
	sf::Texture& texure = holder[ID];
	_sprite.setTexture(texure);
	_sprite.setScale(sf::Vector2f(1, 1));
	std::cout << "TEXTURE LOADED: " << ID << std::endl;
}

Sprite::~Sprite()
{}

sf::Sprite Sprite::GetSprite() const
{
	return _sprite;
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
{
	if (_animation != nullptr)
		_animation->Update(deltaTime);
}

void Sprite::Update(sf::Vector2f direction, int velocity, float deltaTime)
{
	Move(direction, velocity, deltaTime);

	if(_animation != nullptr)
		_animation->Update(deltaTime);
}

void Sprite::Render(RenderWindowRef& rw, float interpolation)
{
	rw->draw(_sprite);
}
