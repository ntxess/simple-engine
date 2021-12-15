#include "ShotParticle.hpp"

ShotParticle::ShotParticle()
{}

ShotParticle::ShotParticle(thor::ResourceHolder<sf::Texture, std::string>& holder, sf::Vector2f position)
{
	InputComponentRef input = std::make_unique<InputComponent>();
	PhysicsComponentRef rb = std::make_unique<PhysicsComponent>();
	SetInput(input);
	SetPhysics(rb);
	SetVelocity(2000.f);
	sf::Texture& texture = holder["Shot"];
	_sprite.setTexture(texture);
	_sprite.setScale(sf::Vector2f(2, 2));
	_sprite.setPosition(position.x + 10, position.y + 10);
	std::cout << "TEXTURE LOADED: " << "Shot" << std::endl;
}

ShotParticle::~ShotParticle()
{}
