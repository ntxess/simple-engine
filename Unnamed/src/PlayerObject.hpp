#pragma once

#include "PlayerInput.hpp"
#include "PlayerPhysics.hpp"
#include "PlayerGraphics.hpp"

class PlayerInput;
class PlayerPhysics;
class PlayerGraphics;

class PlayerObject
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
	std::unique_ptr<PlayerInput> _input;
	std::unique_ptr<PlayerPhysics> _physics;
	std::unique_ptr<PlayerGraphics> _graphics;

public:
	PlayerObject();
	PlayerObject(thor::ResourceHolder<sf::Texture, std::string>& holder, const std::string& ID);
	~PlayerObject();

	PlayerObject::DEFAULT_STATS GetDefaultStats() const;
	PlayerObject::CURRENT_STATS GetCurrentStats() const;
	const std::unique_ptr<PlayerInput>& GetInput() const;
	const std::unique_ptr<PlayerPhysics>& GetPhysics() const;
	const std::unique_ptr<PlayerGraphics>& GetGraphics() const;

	void ResetStats();
	void AugmentHealth(const float& newHealth);
	void AugmentSpeed(const float& newSpeed);
	void AugmentAttackSpeed(const float& newAttackSpeed);
	void InputUpdate(const sf::Event& event);
	void PhysicsUpdate(const float& deltaTime);
	void GraphicsUpdate(const std::unique_ptr<sf::RenderWindow>& rw, const float& interpolation);
};