#include "PlayerNew.hpp"

PlayerNew::PlayerNew()
	: _input(std::make_unique<PlayerInput>())
	, _physics(std::make_unique<PlayerPhysics>())
	, _graphics(std::make_unique<PlayerGraphics>())
{
	_defaultStats.HP = 100.f;
	_defaultStats.SPD = 1.f;
	_defaultStats.ATTACK_SPEED = 1.f;

	ResetStats();
}

PlayerNew::~PlayerNew() 
{}

InputComponentRef& PlayerNew::GetInput()
{
	return _input;
}

PhysicsComponentRef& PlayerNew::GetPhysics()
{
	return _physics;
}

GraphicsComponentRef& PlayerNew::GetGraphics()
{
	return _graphics;
}

void PlayerNew::ResetStats()
{
	_currentStats.HP = _defaultStats.HP;
	_currentStats.SPD = _defaultStats.SPD;
	_currentStats.ATTACK_SPEED = _defaultStats.ATTACK_SPEED;
}

void PlayerNew::AugmentHealth(float newHealth)
{
	_defaultStats.HP = newHealth;
}

void PlayerNew::AugmentSpeed(float newSpeed)
{
	_defaultStats.SPD = newSpeed;
}

void PlayerNew::AugmentAttackSpeed(float newAttackSpeed)
{
	_defaultStats.ATTACK_SPEED = newAttackSpeed;
}
