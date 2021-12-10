#pragma once
#include "Thor/Particles.hpp"
#include "Thor/Math/Distributions.hpp"
#include "Component.hpp"

typedef std::unique_ptr<Component> ComponentRef;

class Player
{
public:
	ComponentRef _component;
	const float _MAX_HEALTH;
	float _attackDamage;
	float _health;
	bool _isShooting;

	Player(ComponentRef& component);
	ComponentRef& GetComponent();
	bool IsAlive() const;
	float GetAttackDamage() const;
	void TakeDamage(float damage);
	void Heal(float healAmount);
	void Shoot(bool isShooting);
	void Update(float deltaTime);
	void Render(RenderWindowRef& rw, float interpolation);
};

