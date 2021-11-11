#pragma once
#include "PhysicsComponent.hpp"
#include "GameObject.hpp"

class RigidbodyBox : public PhysicsComponent
{
private:
	sf::IntRect _boundary;

public:
	RigidbodyBox();
	bool CheckCollision(GameObject& other);
	void Update(float deltaTime);
};