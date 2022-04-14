#include "EnemyPhysics.hpp"

EnemyPhysics::EnemyPhysics()
	: _movementType(nullptr)
{}

EnemyPhysics::~EnemyPhysics()
{}

void EnemyPhysics::SetMovePattern(std::unique_ptr<MovementType> movementType)
{
	_movementType = std::move(movementType);
}

void EnemyPhysics::Update(const EnemyObject& enemy, const float& deltaTime)
{
	if (_movementType->Move(enemy.GetCurrentStats().SPD, deltaTime))
	{
		enemy.GetGraphics()->GetSprite().move(_movementType->GetVelocity());
	}
}