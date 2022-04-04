#pragma once

#include "PhysicsComponent.hpp"
#include "GameObject.hpp"

class PlayerPhysics : public PhysicsComponent
{
private:
	sf::Vector2f _velocity;

public:
	PlayerPhysics();
	~PlayerPhysics();

	sf::Vector2f GetVelocity() const;
	void Update(const GameObject& object, const float& deltaTime);
};
