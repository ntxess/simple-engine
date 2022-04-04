#pragma once

#include "GameObject.hpp"

class GameObject;

class PhysicsComponent
{
public:
	virtual sf::Vector2f GetVelocity() const = 0;
	virtual void Update(const GameObject& object, const float& deltaTime) = 0;
};