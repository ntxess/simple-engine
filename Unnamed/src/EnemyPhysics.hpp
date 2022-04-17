#pragma once
#include <iostream>
#include "EnemyObject.hpp"
#include "WayPoint.hpp"

class EnemyObject;

class EnemyPhysics
{
private:
	WayPoint* _movePattern;
	WayPoint* _path;

	sf::Vector2f _velocity;
	float _distance;
	bool _repeat;

public:
	EnemyPhysics();
	~EnemyPhysics();

	void SetMovePattern(WayPoint* wps, const bool& repeat = false);
	bool TraversePattern(const float& speed, const float& deltaTime);
	void Update(const EnemyObject& enemy, const float& deltaTime);
};