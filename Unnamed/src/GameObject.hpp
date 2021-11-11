#pragma once
#include "InputComponent.hpp"
#include "PhysicsComponent.hpp"
#include "GraphicsComponent.hpp"

typedef std::unique_ptr<sf::RenderWindow> RenderWindowRef;
typedef std::unique_ptr<InputComponent> InputComponentRef;
typedef std::unique_ptr<PhysicsComponent> PhysicsComponentRef;
typedef std::unique_ptr<GraphicsComponent> GraphicsComponentRef;

class GameObject
{
private:
	InputComponentRef _input;
	PhysicsComponentRef _physics;
	GraphicsComponentRef _graphics;

public:
	float _velocity;
	
	GameObject();
	GameObject(GraphicsComponentRef graphics);
	GameObject(PhysicsComponentRef physics, GraphicsComponentRef graphics);
	GameObject(InputComponentRef input, PhysicsComponentRef physics, GraphicsComponentRef graphics);
	~GameObject();
	InputComponentRef& GetInput();
	PhysicsComponentRef& GetPhysics();
	GraphicsComponentRef& GetGraphics();
	const sf::Vector2f& GetDirection();
	const sf::Vector2f& GetPosition();
	void SetVelocity(float velocity);
	void SetScale(sf::Vector2f scale);
	void SetPosition(sf::Vector2f position);
	void PlayAnimation(const std::string& id, bool loop = false);
	void AddAnimation(const std::string &id, const thor::FrameAnimation &animation, sf::Time duration);
	void Update(float deltaTime);
	void Render(RenderWindowRef& rw, float interpolation);
};