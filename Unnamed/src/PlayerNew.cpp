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

void PlayerNew::InputUpdate(sf::Event event)
{
	_input->Update(event);
}

void PlayerNew::PhysicsUpdate(float deltaTime)
{
	_physics->Update(*this, deltaTime);
}

void PlayerNew::GraphicsUpdate(RenderWindowRef& rw, float deltaTime, float interpolation)
{
	_graphics->Animator(*this, deltaTime, interpolation);
	_graphics->Render(rw, interpolation);
}
