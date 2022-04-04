#pragma once

#include "GameObject.hpp"

class GameObject;

class PhysicsComponent
{
public:
	virtual void Update(const GameObject& object, const float& deltaTime) = 0;
};