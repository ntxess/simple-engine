#pragma once
#include "PhysicsComponent.hpp"

class RigidbodyBox : public PhysicsComponent
{
public:
	RigidbodyBox();
	void Move(sf::Sprite& sprite, sf::Vector2f direction, float deltaTime);
	void Update(sf::Sprite& sprite, sf::Vector2f direction, float deltaTime);
};