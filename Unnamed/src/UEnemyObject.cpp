#include "UEnemyObject.hpp"

UEnemyObject::UEnemyObject()
	: _physics(std::make_unique<UEnemyPhysics>())
	, _graphics(std::make_unique<UEnemyGraphics>())
{
	_defaultStats.HP = 1.f;
	_defaultStats.SPD = 1.f;
	_defaultStats.ATTACK_SPEED = 1.f;

	ResetStats();
}

UEnemyObject::UEnemyObject(sf::Texture& texture)
	: _physics(std::make_unique<UEnemyPhysics>())
	, _graphics(std::make_unique<UEnemyGraphics>(texture))
{
	_defaultStats.HP = 100.f;
	_defaultStats.SPD = 500.f;
	_defaultStats.ATTACK_SPEED = 1.f;

	ResetStats();
}

UEnemyObject::~UEnemyObject()
{}

UEnemyObject::DEFAULT_STATS UEnemyObject::GetDefaultStats() const
{
	return _defaultStats;
}

UEnemyObject::CURRENT_STATS UEnemyObject::GetCurrentStats() const
{
	return _currentStats;
}

const std::unique_ptr<UEnemyPhysics>& UEnemyObject::GetPhysics() const
{
	return _physics;
}

const std::unique_ptr<UEnemyGraphics>& UEnemyObject::GetGraphics() const
{
	return _graphics;
}

void UEnemyObject::SetPhysics(std::unique_ptr<UEnemyPhysics>& physics)
{
	_physics = std::move(physics);
}

void UEnemyObject::SetGraphics(std::unique_ptr<UEnemyGraphics>& graphics)
{
	_graphics = std::move(graphics);
}

void UEnemyObject::ResetStats()
{
	_currentStats.HP = _defaultStats.HP;
	_currentStats.SPD = _defaultStats.SPD;
	_currentStats.ATTACK_SPEED = _defaultStats.ATTACK_SPEED;
}

void UEnemyObject::AugmentHealth(const float& newHealth)
{
	_defaultStats.HP = newHealth;
}

void UEnemyObject::AugmentSpeed(const float& newSpeed)
{
	_defaultStats.SPD = newSpeed;
}

void UEnemyObject::AugmentAttackSpeed(const float& newAttackSpeed)
{
	_defaultStats.ATTACK_SPEED = newAttackSpeed;
}

void UEnemyObject::Update(const float& deltaTime)
{
	_physics->Update(_graphics->GetSprite(), _currentStats.SPD, deltaTime);
}

void UEnemyObject::Render(const std::unique_ptr<sf::RenderWindow>& rw, const float& interpolation)
{
	_graphics->Render(rw, interpolation);
}