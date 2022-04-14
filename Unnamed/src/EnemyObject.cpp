#include "EnemyObject.hpp"

EnemyObject::EnemyObject()
	: _physics(std::make_unique<EnemyPhysics>())
	, _graphics(std::make_unique<EnemyGraphics>())
{
	_defaultStats.HP = 1.f;
	_defaultStats.SPD = 1.f;
	_defaultStats.ATTACK_SPEED = 1.f;

	ResetStats();
}

EnemyObject::EnemyObject(thor::ResourceHolder<sf::Texture, std::string>& holder, const std::string& ID)
	: _physics(std::make_unique<EnemyPhysics>())
	, _graphics(std::make_unique<EnemyGraphics>(holder, ID))
{
	_defaultStats.HP = 100.f;
	_defaultStats.SPD = 500.f;
	_defaultStats.ATTACK_SPEED = 1.f;

	ResetStats();
}

EnemyObject::~EnemyObject()
{}

EnemyObject::DEFAULT_STATS EnemyObject::GetDefaultStats() const
{
	return _defaultStats;
}

EnemyObject::CURRENT_STATS EnemyObject::GetCurrentStats() const
{
	return _currentStats;
}

const std::unique_ptr<EnemyPhysics>& EnemyObject::GetPhysics() const
{
	return _physics;
}

const std::unique_ptr<EnemyGraphics>& EnemyObject::GetGraphics() const
{
	return _graphics;
}

void EnemyObject::SetPhysics(std::unique_ptr<EnemyPhysics>& physics)
{
	_physics = std::move(physics);
}

void EnemyObject::SetGraphics(std::unique_ptr<EnemyGraphics>& graphics)
{
	_graphics = std::move(graphics);
}

void EnemyObject::ResetStats()
{
	_currentStats.HP = _defaultStats.HP;
	_currentStats.SPD = _defaultStats.SPD;
	_currentStats.ATTACK_SPEED = _defaultStats.ATTACK_SPEED;
}

void EnemyObject::AugmentHealth(const float& newHealth)
{
	_defaultStats.HP = newHealth;
}

void EnemyObject::AugmentSpeed(const float& newSpeed)
{
	_defaultStats.SPD = newSpeed;
}

void EnemyObject::AugmentAttackSpeed(const float& newAttackSpeed)
{
	_defaultStats.ATTACK_SPEED = newAttackSpeed;
}

void EnemyObject::PhysicsUpdate(const float& deltaTime)
{
	_physics->Update(*this, deltaTime);
}

void EnemyObject::GraphicsUpdate(const std::unique_ptr<sf::RenderWindow>& rw, const float& interpolation)
{
	_graphics->Render(rw, interpolation);
}