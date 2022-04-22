#include "PlayerObject.hpp"

PlayerObject::PlayerObject()
	: _input(std::make_unique<PlayerInput>())
	, _physics(std::make_unique<PlayerPhysics>())
	, _graphics(std::make_unique<PlayerGraphics>())
{
	_defaultStats.HP = 1.f;
	_defaultStats.SPD = 1.f;
	_defaultStats.ATTACK_SPEED = 1.f;

	ResetStats();
}

PlayerObject::PlayerObject(sf::Texture& texture)
	: _input(std::make_unique<PlayerInput>())
	, _physics(std::make_unique<PlayerPhysics>())
	, _graphics(std::make_unique<PlayerGraphics>(texture))
{
	_defaultStats.HP = 100.f;
	_defaultStats.SPD = 500.f;
	_defaultStats.ATTACK_SPEED = 1.f;

	ResetStats();
}

PlayerObject::~PlayerObject()
{}

PlayerObject::DEFAULT_STATS PlayerObject::GetDefaultStats() const
{
    return _defaultStats;
}

PlayerObject::CURRENT_STATS PlayerObject::GetCurrentStats() const
{
    return _currentStats;
}

const std::unique_ptr<PlayerInput>& PlayerObject::GetInput() const
{
	return _input;
}

const std::unique_ptr<PlayerPhysics>& PlayerObject::GetPhysics() const
{
	return _physics;
}

const std::unique_ptr<PlayerGraphics>& PlayerObject::GetGraphics() const
{
	return _graphics;
}

void PlayerObject::ResetStats()
{
	_currentStats.HP = _defaultStats.HP;
	_currentStats.SPD = _defaultStats.SPD;
	_currentStats.ATTACK_SPEED = _defaultStats.ATTACK_SPEED;
}

void PlayerObject::AugmentHealth(const float& newHealth)
{
	_defaultStats.HP = newHealth;
}

void PlayerObject::AugmentSpeed(const float& newSpeed)
{
	_defaultStats.SPD = newSpeed;
}

void PlayerObject::AugmentAttackSpeed(const float& newAttackSpeed)
{
	_defaultStats.ATTACK_SPEED = newAttackSpeed;
}

void PlayerObject::ProcessInput(const sf::Event& event)
{
	_input->Update(event);
}

void PlayerObject::Update(const float& deltaTime)
{
	_physics->Update(*this, deltaTime);
}

void PlayerObject::Render(const std::unique_ptr<sf::RenderWindow>& rw, const float& interpolation)
{
	_graphics->Render(rw, interpolation);
}
