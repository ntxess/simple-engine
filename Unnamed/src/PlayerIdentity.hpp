#pragma once
#include "GameObject.hpp"

typedef std::unique_ptr<Identity> IdentityRef;

class Player
{
public:
	IdentityRef _component;
	const float _MAX_HEALTH;
	float _attackDamage;
	float _health;

	Player(IdentityRef& component);
	IdentityRef& GetComponent();
	bool IsAlive() const;
	float GetAttackDamage() const;
	void TakeDamage(float damage);
	void Heal(float healAmount);
	void Update(float deltaTime);
	void Render(RenderWindowRef& rw, float interpolation);
};

