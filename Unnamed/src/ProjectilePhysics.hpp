#pragma once
#include "PhysicsComponent.hpp"

class ProjectilePhysics : public PhysicsComponent
{
public:	
	ProjectilePhysics();
	void Move(sf::Sprite& sprite, sf::Vector2f direction, float deltaTime);
	void Update(sf::Sprite& sprite, sf::Vector2f direction, float deltaTime);
};

