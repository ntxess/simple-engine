#include "UEnemyPhysics.hpp"

UEnemyPhysics::UEnemyPhysics()
	: _movePattern(nullptr)
	, _path(nullptr)
	, _distance(0.f)
	, _repeat(false)
{}

UEnemyPhysics::~UEnemyPhysics()
{}

void UEnemyPhysics::SetMovePattern(WayPoint* wps, const bool& repeat)
{
	_movePattern = &*wps;
	_path = &*wps;
	_repeat = repeat;
}

sf::Vector2f UEnemyPhysics::TraversePattern(const float& speed, const float& deltaTime)
{
	if (_movePattern == nullptr)
		return sf::Vector2f(0.f, 0.f);

	WayPoint* headPtr = _path;
	WayPoint* nextPtr = headPtr->_nextWP.get();

	if (nextPtr == nullptr)
	{
		if (_repeat)
		{
			_path = _movePattern;
			_distance = 0.f;
		}
		return sf::Vector2f(0.f, 0.f);
	}

	_distance += speed * deltaTime;
	if (_distance > nextPtr->_distanceTotal)
		_path = nextPtr;

	sf::Vector2f unitDist;
	unitDist.x = (nextPtr->_location.x - headPtr->_location.x) / headPtr->_distanceToNext;
	unitDist.y = (nextPtr->_location.y - headPtr->_location.y) / headPtr->_distanceToNext;

	sf::Vector2f velocity;
	velocity.x = unitDist.x * speed * deltaTime;
	velocity.y = unitDist.y * speed * deltaTime;

	return velocity;
}

void UEnemyPhysics::Update(sf::Sprite& object, const float& speed, const float& deltaTime)
{
	object.move(TraversePattern(speed, deltaTime));
}