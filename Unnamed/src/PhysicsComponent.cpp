#include "PhysicsComponent.hpp"

PhysicsComponent::PhysicsComponent()
{}

void PhysicsComponent::Update(sf::Sprite& sprite, sf::Vector2f direction, float deltaTime)
{
	float x = direction.x * deltaTime;
	float y = direction.y * deltaTime;
	sprite.move(x, y);
}
