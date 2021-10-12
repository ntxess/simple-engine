#pragma once

class PhysicsComponent
{
public:
	virtual ~PhysicsComponent() {}
	virtual void Update() = 0;
};