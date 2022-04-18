#pragma once

#include "EnemyPhysics.hpp"
#include "EnemyGraphics.hpp"

class EnemyPhysics;
class EnemyGraphics;

class EnemyObject
{
private:
	struct DEFAULT_STATS
	{
		float HP;
		float SPD;
		float ATTACK_SPEED;
	};

	struct CURRENT_STATS
	{
		float HP;
		float SPD;
		float ATTACK_SPEED;
	};

	DEFAULT_STATS _defaultStats;
	CURRENT_STATS _currentStats;

	// Compartmentalize components to update in different steps of game-loop
	std::unique_ptr<EnemyPhysics> _physics;
	std::unique_ptr<EnemyGraphics> _graphics;

public:
	EnemyObject();
	EnemyObject(sf::Texture& texture);
	~EnemyObject();

	EnemyObject::DEFAULT_STATS GetDefaultStats() const;
	EnemyObject::CURRENT_STATS GetCurrentStats() const;
	const std::unique_ptr<EnemyPhysics>& GetPhysics() const;
	const std::unique_ptr<EnemyGraphics>& GetGraphics() const;
	void SetPhysics(std::unique_ptr<EnemyPhysics>& physics);
	void SetGraphics(std::unique_ptr<EnemyGraphics>& graphics);

	void ResetStats();
	void AugmentHealth(const float& newHealth);
	void AugmentSpeed(const float& newSpeed);
	void AugmentAttackSpeed(const float& newAttackSpeed);
	void PhysicsUpdate(const float& deltaTime);
	void GraphicsUpdate(const std::unique_ptr<sf::RenderWindow>& rw, const float& interpolation);
};

