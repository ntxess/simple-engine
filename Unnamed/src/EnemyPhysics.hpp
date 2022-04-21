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

	float _distance;
	bool _repeat;

public:
	EnemyPhysics();
	~EnemyPhysics();

	void SetMovePattern(WayPoint* wps, const bool& repeat = false);
	sf::Vector2f TraversePattern(const float& speed, const float& deltaTime);
	void Update(sf::Sprite& object, const float& speed, const float& deltaTime);
};