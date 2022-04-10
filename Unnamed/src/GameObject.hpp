#pragma once

#include "InputComponent.hpp"
#include "PhysicsComponent.hpp"
#include "GraphicsComponent.hpp"

class InputComponent;
class PhysicsComponent;
class GraphicsComponent;

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

	DEFAULT_STATS _defaultStats;
	CURRENT_STATS _currentStats;

	// Compartmentalize components to update in different steps of game-loop
	std::shared_ptr<InputComponent> _input;
	std::shared_ptr<PhysicsComponent> _physics;
	std::shared_ptr<GraphicsComponent> _graphics;

public:
	GameObject();
	~GameObject();

	GameObject::DEFAULT_STATS GetDefaultStats() const;
	GameObject::CURRENT_STATS GetCurrentStats() const;
	const std::shared_ptr<InputComponent>& GetInput() const;
	const std::shared_ptr<PhysicsComponent>& GetPhysics() const;
	const std::shared_ptr<GraphicsComponent>& GetGraphics() const;
	void SetInput(std::shared_ptr<InputComponent>& input);
	void SetPhysics(std::shared_ptr<PhysicsComponent>& physics);
	void SetGraphics(std::shared_ptr<GraphicsComponent>& graphics);

	void ResetStats();
	void AugmentHealth(const float& newHealth);
	void AugmentSpeed(const float& newSpeed);
	void AugmentAttackSpeed(const float& newAttackSpeed);
	void InputUpdate(const sf::Event& event);
	void PhysicsUpdate(const float& deltaTime);
	void GraphicsUpdate(const std::unique_ptr<sf::RenderWindow>& rw, const float& interpolation);
}; 