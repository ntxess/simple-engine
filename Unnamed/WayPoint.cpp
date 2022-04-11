#include "WayPoint.hpp"

WayPoint::WayPoint(sf::Vector2f location)
	: _location(location)
	, _distanceToNext(0.f)
	, _distanceTotal(0.f)
{}

WayPoint::~WayPoint()
{}

void WayPoint::AddNext(std::unique_ptr<WayPoint> wayPoint)
{
	_next = std::move(wayPoint);
	_distanceToNext = sqrt((_next->_location.x - _location.x) * 
						   (_next->_location.x - _location.x) + 
						   (_next->_location.y - _location.y) * 
						   (_next->_location.y - _location.y));

	_next->_distanceTotal = _distanceTotal + _distanceToNext;
}
