#pragma once
#include "PhysicsComponent.hpp"
#include "GameObject.hpp"

class BoxCollider : public PhysicsComponent
{
private:
	sf::IntRect _boundary;

public:
	BoxCollider();
	bool CheckCollision(GameObject& other);
	void Update(float deltaTime);
};