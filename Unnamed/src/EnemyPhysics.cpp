#include "EnemyPhysics.hpp"

EnemyPhysics::EnemyPhysics()
	: _movePattern(nullptr)
	, _path(nullptr)
	, _velocity(sf::Vector2f(0.f, 0.f))
	, _distance(0.f)
	, _repeat(false)
{}

EnemyPhysics::~EnemyPhysics()
{}

void EnemyPhysics::SetMovePattern(WayPoint* wps, const bool& repeat)
{
	_movePattern = &*wps;
	_path = &*wps;
	_repeat = repeat;
}

bool EnemyPhysics::TraversePattern(const float& speed, const float& deltaTime)
{
	WayPoint* headPtr = _path;
	WayPoint* nextPtr;

	nextPtr = headPtr->_nextWP.get();
	if (nextPtr == nullptr)
		return false;

	_distance += speed * deltaTime;
	if (_distance > nextPtr->_distanceTotal)
		_path = nextPtr;

	nextPtr = headPtr->_nextWP.get();
	sf::Vector2f unitDist;
	unitDist.x = (nextPtr->_location.x - headPtr->_location.x) / headPtr->_distanceToNext;
	unitDist.y = (nextPtr->_location.y - headPtr->_location.y) / headPtr->_distanceToNext;

	sf::Vector2f velocity;
	_velocity.x = unitDist.x * speed * deltaTime;
	_velocity.y = unitDist.y * speed * deltaTime;

	if (_repeat && _path->_distanceToNext == 0)
	{
		_path = _movePattern;
		_distance = 0.f;
	}

	return true;
}

void EnemyPhysics::Update(sf::Sprite& object, const float& speed, const float& deltaTime)
{
	if (TraversePattern(speed, deltaTime))
	{
		object.move(_velocity);
	}
}