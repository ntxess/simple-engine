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

void EnemyPhysics::SetMovePattern(std::unique_ptr<WayPoint> wps, const bool& repeat)
{
	_movePattern = std::move(wps);
	_path = _movePattern.get();
	_repeat = repeat;

	WayPoint* headPtr = _movePattern.get();
	WayPoint* next;
	while (headPtr != NULL)
	{
		std::cout << "=========================Physics=========================" << std::endl;
		next = headPtr->_nextWP.get();
		std::cout << "ADDRESS   : " << &*(headPtr) << " " << &*(headPtr->_nextWP) << std::endl;
		std::cout << "LOCATION  : " << headPtr->_location.x << " " << headPtr->_location.y << std::endl;
		std::cout << "DISTANCE N: " << headPtr->_distanceToNext << std::endl;
		std::cout << "DISTANCE T: " << headPtr->_distanceTotal << std::endl;
		headPtr = next;
	}
}

bool EnemyPhysics::TraversePattern(const float& speed, const float& deltaTime)
{
	_velocity = sf::Vector2f(0.f, 0.f);
	if (_path->_nextWP.get())
	{
		_distance += speed * deltaTime;
		std::cout << "**********************************************" << std::endl;
		std::cout << "DEBUG DISTANCE   : " << _distance << std::endl;
		std::cout << "DEBUG DISTANCE T : " << _path->_nextWP.get()->_distanceTotal << std::endl;
		if (_distance > _path->_nextWP.get()->_distanceTotal)
			_path = _path->_nextWP.get();
	}

	if (_path->_nextWP.get())
	{
		sf::Vector2f unitDist;
		unitDist.x = (_path->_nextWP.get()->_location.x - _path->_location.x) / _path->_distanceToNext;
		unitDist.y = (_path->_nextWP.get()->_location.y - _path->_location.y) / _path->_distanceToNext;

		sf::Vector2f velocity;
		_velocity.x = unitDist.x * speed * deltaTime;
		_velocity.y = unitDist.y * speed * deltaTime;

		std::cout << "DEBUG LOCATION   : " << _path->_location.x << " " << _path->_location.y << std::endl;
		std::cout << "DEBUG LOCATION N : " << _path->_nextWP.get()->_location.x << " " << _path->_nextWP.get()->_location.y << std::endl;
		std::cout << "DEBUG DISTANCE N : " << _path->_distanceToNext << std::endl;
		std::cout << "DEBUG UNITDIST   : " << unitDist.x << " " << unitDist.y << std::endl;
		std::cout << "DEBUG VELOCITY   : " << _velocity.x << " " << _velocity.y << std::endl;

		return true;
	}

	if (_repeat)
	{
		_path = _movePattern.get();
		_distance = 0.f;
	}

	return false;
}

void EnemyPhysics::Update(const EnemyObject& enemy, const float& deltaTime)
{
	if (TraversePattern(enemy.GetCurrentStats().SPD, deltaTime))
	{
		enemy.GetGraphics()->GetSprite().move(_velocity);
	}
}