#pragma once

#include "WayPoint.hpp"

class MovementType
{
public:
	virtual sf::Vector2f GetVelocity() const = 0;
	virtual bool Move(const float& speed, const float& deltaTime) = 0;
};