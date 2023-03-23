#pragma once
#include "SFML/Graphics/Vertex.hpp"
#include <memory>

class Waypoint
{
public:
	sf::Vector2f location;
	float distanceToNext;
	float distanceTotal;
	std::unique_ptr<Waypoint> nextWP;

public:
	Waypoint();
	Waypoint(sf::Vector2f location);
	~Waypoint() = default;

	void AddNext(std::unique_ptr<Waypoint> waypoint);
};

