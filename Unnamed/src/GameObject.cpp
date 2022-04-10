#include "GameObject.hpp"

GameObject::GameObject()
	: _input(nullptr)
	, _physics(nullptr)
	, _graphics(nullptr)
{
	_defaultStats.HP = 100.f;
	_defaultStats.SPD = 500.f;
	_defaultStats.ATTACK_SPEED = 1.f;

	ResetStats();
}

GameObject::~GameObject()
{}

GameObject::DEFAULT_STATS GameObject::GetDefaultStats() const
{
	return _defaultStats;
}

GameObject::CURRENT_STATS GameObject::GetCurrentStats() const
{
	return _currentStats;
}

const std::shared_ptr<InputComponent>& GameObject::GetInput() const
{
	return _input;
}

const std::shared_ptr<PhysicsComponent>& GameObject::GetPhysics() const
{
	return _physics;
}

const std::shared_ptr<GraphicsComponent>& GameObject::GetGraphics() const
{
	return _graphics;
}

void GameObject::SetInput(std::shared_ptr<InputComponent>& input)
{
	_input = input;
}

void GameObject::SetPhysics(std::shared_ptr<PhysicsComponent>& physics)
{
	_physics = physics;
}

void GameObject::SetGraphics(std::shared_ptr<GraphicsComponent>& graphics)
{
	_graphics = graphics;
}

void GameObject::ResetStats()
{
	_currentStats.HP = _defaultStats.HP;
	_currentStats.SPD = _defaultStats.SPD;
	_currentStats.ATTACK_SPEED = _defaultStats.ATTACK_SPEED;
}

void GameObject::AugmentHealth(const float& newHealth)
{
	_defaultStats.HP = newHealth;
}

void GameObject::AugmentSpeed(const float& newSpeed)
{
	_defaultStats.SPD = newSpeed;
}

void GameObject::AugmentAttackSpeed(const float& newAttackSpeed)
{
	_defaultStats.ATTACK_SPEED = newAttackSpeed;
}

void GameObject::InputUpdate(const sf::Event& event)
{
	_input->Update(event);
}

void GameObject::PhysicsUpdate(const float& deltaTime)
{
	_physics->Update(*this, deltaTime);
}

void GameObject::GraphicsUpdate(const std::unique_ptr<sf::RenderWindow>& rw, const float& interpolation)
{
	_graphics->Render(rw, interpolation);
}