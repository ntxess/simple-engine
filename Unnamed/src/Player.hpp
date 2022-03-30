#pragma once
#include <Thor/Particles.hpp>
#include <Thor/Math/Distributions.hpp>
#include "GameObject.hpp"

typedef std::unique_ptr<GameObject> GameObjectRef;

class Player
{
public:
	GameObjectRef _component;
	const float _MAX_HEALTH;
	float _attackDamage;
	float _health;
	bool _isShooting;

	Player(thor::ResourceHolder<sf::Texture, std::string>& holder, std::string ID);
	GameObjectRef& GetComponent();
	bool IsAlive() const;
	float GetAttackDamage() const;
	void TakeDamage(float damage);
	void Heal(float healAmount);
	void Shoot(bool isShooting);
	void Update(float deltaTime);
	void Render(RenderWindowRef& rw, float interpolation);
};

