#include "PlayerIdentity.hpp"

PlayerIdentity::PlayerIdentity()
	: _MAX_HEALTH(1000), _attackDamage(10), _health(_MAX_HEALTH)
{}

const bool PlayerIdentity::IsAlive()
{
	return _health > 0 ? true : false;
}

const float PlayerIdentity::GetAttackDamage()
{
	return _attackDamage;
}

void PlayerIdentity::TakeDamage(float damage)
{
	if (_health > 0.f)
		_health -= damage;
}

void PlayerIdentity::Heal(float healAmount)
{
	_health += healAmount;
	if (_MAX_HEALTH > _health)
		_health = _MAX_HEALTH;
}

