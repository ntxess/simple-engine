#pragma once
#include <SFML/Graphics.hpp>
#include "InputComponent.hpp"
#include "PhysicsComponent.hpp"
#include "GraphicsComponent.hpp"

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
	int _x, _y;
	
	GameObject();
	GameObject(InputComponentRef input, PhysicsComponentRef physics, GraphicsComponentRef graphics);
	~GameObject();
	InputComponentRef& Input();
	PhysicsComponentRef& Physics();
	GraphicsComponentRef& Graphics();
	virtual void Update(double deltaTime);
	virtual void Render(sf::RenderWindow* rt, double interpolation);
};