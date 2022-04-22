#pragma once

#include "UEnemyPhysics.hpp"
#include "UEnemyGraphics.hpp"

class UEnemyPhysics;
class UEnemyGraphics;

class UEnemyObject
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
	std::unique_ptr<UEnemyPhysics> _physics;
	std::unique_ptr<UEnemyGraphics> _graphics;

public:
	UEnemyObject();
	UEnemyObject(sf::Texture& texture);
	~UEnemyObject();

	UEnemyObject::DEFAULT_STATS GetDefaultStats() const;
	UEnemyObject::CURRENT_STATS GetCurrentStats() const;
	const std::unique_ptr<UEnemyPhysics>& GetPhysics() const;
	const std::unique_ptr<UEnemyGraphics>& GetGraphics() const;
	void SetPhysics(std::unique_ptr<UEnemyPhysics>& physics);
	void SetGraphics(std::unique_ptr<UEnemyGraphics>& graphics);

	void ResetStats();
	void AugmentHealth(const float& newHealth);
	void AugmentSpeed(const float& newSpeed);
	void AugmentAttackSpeed(const float& newAttackSpeed);
	void Update(const float& deltaTime);
	void Render(const std::unique_ptr<sf::RenderWindow>& rw, const float& interpolation);
};