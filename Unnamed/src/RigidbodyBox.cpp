#include "RigidbodyBox.hpp"

RigidbodyBox::RigidbodyBox()
{}

void RigidbodyBox::Move(sf::Sprite& sprite, sf::Vector2f direction, float deltaTime)
{
	float x = direction.x * deltaTime;
	float y = direction.y * deltaTime;
	sprite.move(x, y);
}

void RigidbodyBox::Update(sf::Sprite& sprite, sf::Vector2f direction, float deltaTime)
{
	Move(sprite, direction, deltaTime);
}
