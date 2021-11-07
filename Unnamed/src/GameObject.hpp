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
	void SetVelocity(float velocity);
	void Update(float deltaTime);
	void Render(RenderWindowRef& rw, float interpolation);
};