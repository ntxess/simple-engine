#pragma once
#include "PhysicsComponent.hpp"

class RigidbodyBox : public PhysicsComponent
{
private:

public:
	RigidbodyBox();
	void Update(float deltaTime);
};