#pragma once

class Animation
{
public:
	virtual ~Animation() = 0;
	virtual void Update(float deltaTime) = 0;
};