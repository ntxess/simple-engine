#include "Particle.hpp"

Particle::Particle() 
	: _inUse(false)
{}

Particle::~Particle()
{}

Particle* Particle::GetNext() const
{
	return _state.next;
}

void Particle::Init(thor::ResourceHolder<sf::Texture, std::string>& holder, const std::string& ID, const sf::Vector2f emitterPos)
{
	sf::Texture& texture = holder[ID];
	_sprite.setTexture(texture);
	_sprite.setScale(sf::Vector2f(2, 2));
	_sprite.setPosition(emitterPos);
	_inUse = true;
	std::cout << "TEXTURE LOADED: " << ID << std::endl;
}

void Particle::SetNext(Particle* next)
{
	_state.next = next;
}

void Particle::Update(const float& deltaTime)
{

}

bool Particle::Render(const RenderWindowRef& rw, const float& deltaTime, const float& interpolation)
{
	return false;
}