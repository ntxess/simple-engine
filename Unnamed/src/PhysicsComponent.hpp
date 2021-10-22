#pragma once

class PhysicsComponent
{
public:
	virtual ~PhysicsComponent() {}
	virtual void Update(float deltaTime) = 0;
};