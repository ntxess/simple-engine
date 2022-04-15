#include "WayPoint.hpp"

WayPoint::WayPoint()
	: _location(sf::Vector2f(0.f, 0.f))
	, _distanceToNext(0.f)
	, _distanceTotal(0.f)
	, _nextWP(nullptr)
{}

WayPoint::WayPoint(sf::Vector2f location)
	: _location(location)
	, _distanceToNext(0.f)
	, _distanceTotal(0.f)
	, _nextWP(nullptr)
{}

WayPoint::~WayPoint()
{}

void WayPoint::AddNext(std::unique_ptr<WayPoint> wayPoint)
{
	_nextWP = std::move(wayPoint);

	_distanceToNext = sqrt((_nextWP->_location.x - _location.x) *
						   (_nextWP->_location.x - _location.x) +
						   (_nextWP->_location.y - _location.y) * 
						   (_nextWP->_location.y - _location.y));

	_nextWP->_distanceTotal = _distanceTotal + _distanceToNext;
}
