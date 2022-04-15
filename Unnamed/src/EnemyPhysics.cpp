#include "EnemyPhysics.hpp"

EnemyPhysics::EnemyPhysics()
	: _head(nullptr)
	, _path(nullptr)
	, _velocity(sf::Vector2f(0.f, 0.f))
	, _distance(0.f)
	, _repeat(false)
{}

EnemyPhysics::~EnemyPhysics()
{
	WayPoint* next;
	while (_head != NULL)
	{
		next = _head->_nextWP;
		delete _head;
		_head = next;
	}
}

void EnemyPhysics::SetMovePattern(WayPoint* wps, const bool& repeat)
{
	_head = wps;
	_path = wps;
	_repeat = repeat;
}

bool EnemyPhysics::TraversePattern(const float& speed, const float& deltaTime)
{
	_velocity = sf::Vector2f(0.f, 0.f);
	if (_path->_nextWP)
	{
		_distance += speed * deltaTime;
		if (_distance > _path->_nextWP->_distanceTotal)
			_path = std::move(_path->_nextWP);
	}

	if (_path->_nextWP)
	{
		sf::Vector2f unitDist;
		unitDist.x = (_path->_nextWP->_location.x - _path->_location.x) / _path->_distanceToNext;
		unitDist.y = (_path->_nextWP->_location.y - _path->_location.y) / _path->_distanceToNext;

		sf::Vector2f velocity;
		_velocity.x = unitDist.x * speed * deltaTime;
		_velocity.y = unitDist.y * speed * deltaTime;
		return true;
	}

	if (_repeat)
	{
		_path = _head;
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