#include "CircleMov.hpp"

CircleMov::CircleMov()
{
	WayPoint* pointA = new WayPoint(sf::Vector2f(120.0f, 80.0f));
	WayPoint* pointB = new WayPoint(sf::Vector2f(210.0f, 30.0f));
	WayPoint* pointC = new WayPoint(sf::Vector2f(260.0f, 120.0f));
	WayPoint* pointD = new WayPoint(sf::Vector2f(180.0f, 190.0f));
	WayPoint* pointE = new WayPoint(sf::Vector2f(80.0f, 140.0f));

	pointA->AddNext(pointB);
	pointB->AddNext(pointC);
	pointC->AddNext(pointD);
	pointD->AddNext(pointE);
	_currentWP = pointA;
	_headWP = pointA;
}

CircleMov::~CircleMov()
{
	WayPoint* temp;
	while (_headWP)
	{
		temp = _headWP;
		_headWP = _headWP->_nextWP;
		delete temp;
	}
}

sf::Vector2f CircleMov::GetVelocity() const
{
    return _velocity;
}

bool CircleMov::Move(const float& speed, const float& deltaTime)
{
	_velocity = sf::Vector2f(0.f, 0.f);

	float deltaSpeed = speed * deltaTime;
	if (_currentWP->_nextWP)
	{
		_distance += deltaSpeed;
		if (_distance > _currentWP->_nextWP->_distanceTotal)
			_currentWP = _currentWP->_nextWP;
	} 

	if (_currentWP->_nextWP)
	{
		sf::Vector2f unitDist;
		unitDist.x = (_currentWP->_nextWP->_location.x - _currentWP->_location.x) / _currentWP->_distanceToNext;
		unitDist.y = (_currentWP->_nextWP->_location.y - _currentWP->_location.y) / _currentWP->_distanceToNext;

		_velocity.x = unitDist.x * speed * deltaTime;
		_velocity.y = unitDist.y * speed * deltaTime;
		return true;
	}

	_currentWP = _headWP;
	_distance = 0;
	return false;
}
