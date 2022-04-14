#pragma once

#include "EnemyObject.hpp"
#include "MovementType.hpp"

class EnemyObject;

class EnemyPhysics
{
private:
	std::unique_ptr<MovementType> _movementType;

public:
	EnemyPhysics();
	~EnemyPhysics();

	void SetMovePattern(std::unique_ptr<MovementType> movementType);
	void Update(const EnemyObject& enemy, const float& deltaTime);
};