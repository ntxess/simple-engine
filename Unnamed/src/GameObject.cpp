#include "GameObject.hpp"

GameObject::GameObject() 
{
	_velocity = 0;
	_x = 0;
	_y = 0;
}

GameObject::GameObject(InputComponentRef input, PhysicsComponentRef physics, GraphicsComponentRef graphics)
{
	_velocity = 0;
	_x = 0;
	_y = 0;
	_input = std::move(input);
	_physics = std::move(physics);
	_graphics = std::move(graphics);
}

GameObject::~GameObject()
{}


InputComponentRef& GameObject::Input()
{
	return _input;
}

PhysicsComponentRef& GameObject::Physics()
{
	return _physics;
}

GraphicsComponentRef& GameObject::Graphics()
{
	return _graphics;
}

void GameObject::Update(float deltaTime)
{
	if(_graphics)
		_graphics->Update(deltaTime);
	if(_physics)
		_physics->Update(deltaTime);
}

void GameObject::Render(RenderWindowRef& rw, float interpolation)
{
	if(_graphics)
		_graphics->Render(rw, interpolation);
}

