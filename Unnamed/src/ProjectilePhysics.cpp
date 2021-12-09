#include "ProjectilePhysics.hpp"

ProjectilePhysics::ProjectilePhysics()
{}

void ProjectilePhysics::Move(sf::Sprite& sprite, sf::Vector2f direction, float deltaTime)
{
	float x = 20 * deltaTime;
	float y = 50 * deltaTime;
	sprite.move(x, y);
}

void ProjectilePhysics::Update(sf::Sprite& sprite, sf::Vector2f direction, float deltaTime)
{
	Move(sprite, direction, deltaTime);
}
