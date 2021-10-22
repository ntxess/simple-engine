#pragma once

class PhysicsComponent
{
public:
	virtual ~PhysicsComponent() {}
	virtual void Update(double deltaTime) = 0;
};