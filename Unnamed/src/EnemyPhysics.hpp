#pragma once

#include "EnemyObject.hpp"
#include "WayPoint.hpp"

class EnemyObject;

class EnemyPhysics
{
private:
	std::unique_ptr<WayPoint> _path;
	float _distance;

public:
	EnemyPhysics();
	~EnemyPhysics();

	void SetPath(std::unique_ptr<WayPoint> wayPoint);
	void Update(const EnemyObject& enemy, const float& deltaTime);
};