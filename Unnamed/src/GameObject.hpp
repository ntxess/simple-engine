#pragma once
#include <Thor/Resources.hpp>

#include "InputComponent.hpp"
#include "PhysicsComponent.hpp"
#include "GraphicsComponent.hpp"

class InputComponent;
class PhysicsComponent;
class GraphicsComponent;

typedef std::unique_ptr<sf::RenderWindow> RenderWindowRef;
typedef std::shared_ptr<InputComponent> InputComponentRef;
typedef std::shared_ptr<PhysicsComponent> PhysicsComponentRef;
typedef std::shared_ptr<GraphicsComponent> GraphicsComponentRef;

class GameObject
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

	// Compartmentalize components to update in different steps of game-loop
	InputComponentRef _input;
	PhysicsComponentRef _physics;
	GraphicsComponentRef _graphics;

	DEFAULT_STATS _defaultStats;
	CURRENT_STATS _currentStats;

public:
	GameObject();
	~GameObject();

	const InputComponentRef& GetInput() const;
	const PhysicsComponentRef& GetPhysics() const;
	const GraphicsComponentRef& GetGraphics() const;
	void SetInput(InputComponentRef& input);
	void SetPhysics(PhysicsComponentRef& physics);
	void SetGraphics(GraphicsComponentRef& graphics);

	GameObject::DEFAULT_STATS GetDefaultStats() const;
	GameObject::CURRENT_STATS GetCurrentStats() const;
	void ResetStats();
	void AugmentHealth(const float& newHealth);
	void AugmentSpeed(const float& newSpeed);
	void AugmentAttackSpeed(const float& newAttackSpeed);
	void InputUpdate(const sf::Event& event);
	void PhysicsUpdate(const float& deltaTime);
	void GraphicsUpdate(const RenderWindowRef& rw, const float& deltaTime, const float& interpolation);
}; 