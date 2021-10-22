#pragma once
#include <SFML/Graphics.hpp>
#include "InputComponent.hpp"
#include "PhysicsComponent.hpp"
#include "GraphicsComponent.hpp"

class GameObject
{
private:
	InputComponent* _input;
	PhysicsComponent* _physics;
	GraphicsComponent* _graphics;

public:
	int _velocity;
	int _x, _y;
	
	GameObject();
	GameObject(InputComponent* input, PhysicsComponent* physics, GraphicsComponent* graphics);
	~GameObject();
	InputComponent* Input();
	PhysicsComponent* Physics();
	GraphicsComponent* Graphics();
	virtual void Update(double deltaTime);
	virtual void Render(sf::RenderTarget* rt, double interpolation);
};