#pragma once
#include <SFML/Graphics.hpp>
#include <Thor/Resources.hpp>

#include "PlayerInput.hpp"
#include "PlayerPhysics.hpp"
#include "PlayerGraphics.hpp"

class PlayerInput;
class PlayerPhysics;
class PlayerGraphics;

typedef std::unique_ptr<sf::RenderWindow> RenderWindowRef;
typedef std::unique_ptr<PlayerInput> PlayerInputRef;
typedef std::unique_ptr<PlayerPhysics> PlayerPhysicsRef;
typedef std::unique_ptr<PlayerGraphics> PlayerGraphicsRef;

class Player
{
	friend class PlayerInput;
	friend class PlayerPhysics;
	friend class PlayerGraphics;

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

	// Compartmentalize components to update in different steps of game-loop
	PlayerInputRef _input;
	PlayerPhysicsRef _physics;
	PlayerGraphicsRef _graphics;

	DEFAULT_STATS _defaultStats;
	CURRENT_STATS _currentStats;

public:
	Player();
	Player(thor::ResourceHolder<sf::Texture, std::string>& holder, std::string ID);
	~Player();

	const PlayerInputRef& GetInput() const;
	const PlayerPhysicsRef& GetPhysics() const;
	const PlayerGraphicsRef& GetGraphics() const;

	void ResetStats();
	void AugmentHealth(const float& newHealth);
	void AugmentSpeed(const float& newSpeed);
	void AugmentAttackSpeed(const float& newAttackSpeed);
	void InputUpdate(const sf::Event& event);
	void PhysicsUpdate(const float& deltaTime);
	void GraphicsUpdate(const RenderWindowRef& rw, const float& deltaTime, const float& interpolation);
};