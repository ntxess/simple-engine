#pragma once
#include "WayPoint.hpp"

class UEnemyPhysics
{
private:
	WayPoint* _movePattern;
	WayPoint* _path;

	float _distance;
	bool _repeat;

public:
	UEnemyPhysics();
	~UEnemyPhysics();

	void SetMovePattern(WayPoint* wps, const bool& repeat = false);
	sf::Vector2f TraversePattern(const float& speed, const float& deltaTime);
	void Update(sf::Sprite& object, const float& speed, const float& deltaTime);
};