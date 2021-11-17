#pragma once

class PlayerIdentity
{
public:
	const float _MAX_HEALTH;
	float _attackDamage;
	float _health;

	PlayerIdentity();
	const bool IsAlive();
	const float GetAttackDamage();
	void TakeDamage(float damage);
	void Heal(float healAmount);
};

