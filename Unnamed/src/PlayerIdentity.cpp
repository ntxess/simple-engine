#include "PlayerIdentity.hpp"

Player::Player(ComponentRef& component)
	: _component(std::move(component)), _MAX_HEALTH(1000), _attackDamage(10), _health(_MAX_HEALTH)
{}

ComponentRef& Player::GetComponent()
{
	return _component;
}

bool Player::IsAlive() const
{
	return _health > 0 ? true : false;
}

float Player::GetAttackDamage() const
{
	return _attackDamage;
}

void Player::TakeDamage(float damage)
{
	if (_health > 0.f)
		_health -= damage;
}

void Player::Heal(float healAmount)
{
	_health += healAmount;
	if (_MAX_HEALTH > _health)
		_health = _MAX_HEALTH;
}

void Player::Update(float deltaTime)
{
	_component->Update(deltaTime);
}

void Player::Render(RenderWindowRef& rw, float interpolation)
{
	_component->Render(rw, interpolation);
}

