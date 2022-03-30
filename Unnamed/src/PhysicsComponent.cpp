#include "PhysicsComponent.hpp"

PhysicsComponent::PhysicsComponent()
{}

void PhysicsComponent::Update(sf::Sprite& sprite, sf::Vector2f direction, float deltaTime)
{
	float x = direction.x * deltaTime * 0.99f;
	float y = direction.y * deltaTime * 0.99f;
	sprite.move(x, y);
}
