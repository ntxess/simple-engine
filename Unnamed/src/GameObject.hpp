#pragma once
#include <SFML/Graphics.hpp>
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
	int _velocity;
	int _x;
	int _y;
	
	GameObject(GraphicsComponentRef graphics);
	GameObject(PhysicsComponentRef physics, GraphicsComponentRef graphics);
	GameObject(InputComponentRef input, PhysicsComponentRef physics, GraphicsComponentRef graphics);
	~GameObject();
	InputComponentRef& Input();
	PhysicsComponentRef& Physics();
	GraphicsComponentRef& Graphics();
	virtual void Update(float deltaTime);
	virtual void Render(RenderWindowRef& rw, float interpolation);
};