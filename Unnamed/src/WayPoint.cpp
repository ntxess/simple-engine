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
{
	delete _nextWP;
}

void WayPoint::AddNext(WayPoint* wayPoint)
{
	_nextWP = wayPoint;

	_distanceToNext = sqrt((_nextWP->_location.x - _location.x) *
						   (_nextWP->_location.x - _location.x) +
						   (_nextWP->_location.y - _location.y) * 
						   (_nextWP->_location.y - _location.y));

	_nextWP->_distanceTotal = _distanceTotal + _distanceToNext;
}
