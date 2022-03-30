#pragma once
#include <SFML/Graphics.hpp>
#include <Thor/Resources.hpp>

#include "PlayerInput.hpp"
#include "PlayerPhysics.hpp"
#include "PlayerGraphics.hpp"

typedef std::unique_ptr<PlayerInput> InputComponentRef;
typedef std::unique_ptr<PlayerPhysics> PhysicsComponentRef;
typedef std::unique_ptr<PlayerGraphics> GraphicsComponentRef;

class PlayerNew
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

	// Compartmentalize components to update in different steps
	InputComponentRef _input;
	PhysicsComponentRef _physics;
	GraphicsComponentRef _graphics;

	DEFAULT_STATS _defaultStats;
	CURRENT_STATS _currentStats;

public:
	PlayerNew();
	~PlayerNew();

	InputComponentRef& GetInput();
	PhysicsComponentRef& GetPhysics();
	GraphicsComponentRef& GetGraphics();

	void ResetStats();
	void AugmentHealth(float newHealth);
	void AugmentSpeed(float newSpeed);
	void AugmentAttackSpeed(float newAttackSpeed);
};