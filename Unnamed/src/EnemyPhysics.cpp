#include "EnemyPhysics.hpp"

EnemyPhysics::EnemyPhysics()
	: _path(nullptr)
	, _distance(0.f)
{}

EnemyPhysics::~EnemyPhysics()
{}

void EnemyPhysics::SetPath(std::unique_ptr<WayPoint> wayPoint)
{
	_path = std::move(wayPoint);
}


void EnemyPhysics::Update(const EnemyObject& enemy, const float& deltaTime)
{
	if (_path->_nextWP)
	{
		_distance += enemy.GetCurrentStats().SPD * deltaTime;
		if(_distance > _path->_nextWP->_distanceTotal)
			_path = std::move(_path->_nextWP);
	}

	if (_path->_nextWP)
	{
		sf::Vector2f unitDist;
		unitDist.x = (_path->_nextWP->_location.x - _path->_location.x) / _path->_distanceToNext;
		unitDist.y = (_path->_nextWP->_location.y - _path->_location.y) / _path->_distanceToNext;

		sf::Vector2f velocity;
		velocity.x = unitDist.x * enemy.GetCurrentStats().SPD * deltaTime;
		velocity.y = unitDist.y * enemy.GetCurrentStats().SPD * deltaTime;
		enemy.GetGraphics()->GetSprite().move(velocity);
	}
}