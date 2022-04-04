#pragma once

#include "PhysicsComponent.hpp"
#include "GameObject.hpp"

class GameObject;

class AIPhysics : public PhysicsComponent
{
private:
	sf::Vector2f _velocity;

public:
	AIPhysics();
	~AIPhysics();

	void Update(const GameObject& object, const float& deltaTime);
};

