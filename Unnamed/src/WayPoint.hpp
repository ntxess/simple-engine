#pragma once

#include "SFML/Graphics.hpp"

class WayPoint
{
public:
	sf::Vector2f _location;
	float _distanceToNext;
	float _distanceTotal;
	std::unique_ptr<WayPoint> _nextWP;

public:
	WayPoint();
	WayPoint(sf::Vector2f location);
	~WayPoint();

	void AddNext(std::unique_ptr<WayPoint> wayPoint);
};

