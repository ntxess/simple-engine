#pragma once

#include "MovementType.hpp"
#include "WayPoint.hpp"

class CircleMov : public MovementType
{
private:
	WayPoint* _headWP;
	WayPoint* _currentWP;
	sf::Vector2f _velocity;
	float _distance;

public:
	CircleMov();
	~CircleMov();

	sf::Vector2f GetVelocity() const;
	bool Move(const float& speed, const float& deltaTime);
};

