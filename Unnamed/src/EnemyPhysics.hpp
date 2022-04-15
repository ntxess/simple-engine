#pragma once

#include "EnemyObject.hpp"
#include "WayPoint.hpp"

class EnemyObject;

class EnemyPhysics
{
private:
	std::unique_ptr<WayPoint> _movePattern;
	WayPoint* _path;

	sf::Vector2f _velocity;
	float _distance;
	bool _repeat;

public:
	EnemyPhysics();
	~EnemyPhysics();

	void SetMovePattern(std::unique_ptr<WayPoint> wps, const bool& repeat = false);
	bool TraversePattern(const float& speed, const float& deltaTime);
	void Update(const EnemyObject& enemy, const float& deltaTime);
};