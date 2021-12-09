#pragma once
#include "Component.hpp"

typedef std::unique_ptr<Component> ComponentRef;

class Player
{
public:
	ComponentRef _component;
	const float _MAX_HEALTH;
	float _attackDamage;
	float _health;

	Player(ComponentRef& component);
	ComponentRef& GetComponent();
	bool IsAlive() const;
	float GetAttackDamage() const;
	void TakeDamage(float damage);
	void Heal(float healAmount);
	void Update(float deltaTime);
	void Render(RenderWindowRef& rw, float interpolation);
};

