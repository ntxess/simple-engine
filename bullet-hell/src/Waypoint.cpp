#include "WayPoint.hpp"

Waypoint::Waypoint()
	: location(sf::Vector2f(0.f, 0.f))
	, distanceToNext(0.f)
	, distanceTotal(0.f)
	, nextWP(nullptr)
{}

Waypoint::Waypoint(sf::Vector2f location)
	: location(location)
	, distanceToNext(0.f)
	, distanceTotal(0.f)
	, nextWP(nullptr)
{}

void Waypoint::AddNext(std::unique_ptr<Waypoint> waypoint)
{
	nextWP = std::move(waypoint);

	distanceToNext = sqrt((nextWP->location.x - location.x) *
						  (nextWP->location.x - location.x) +
						  (nextWP->location.y - location.y) * 
						  (nextWP->location.y - location.y));
}
