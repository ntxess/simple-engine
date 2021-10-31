#include "Sprite.hpp"

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

void Sprite::Update(float deltaTime)
{
	if(_animation != nullptr)
		_animation->Update(deltaTime);
}

void Sprite::Render(RenderWindowRef& rw, float interpolation)
{
	rw->draw(_sprite);
}
