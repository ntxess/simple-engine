#include "GameObject.hpp"

GameObject::GameObject(GraphicsComponentRef graphics)
	: _velocity(0),
	_x(0),
	_y(0),
	_input(nullptr),
	_physics(nullptr),
	_graphics(std::move(graphics))
{}

GameObject::GameObject(PhysicsComponentRef physics, GraphicsComponentRef graphics)
	: GameObject(std::move(graphics))
{
	_physics = std::move(physics);
}

GameObject::GameObject(InputComponentRef input, PhysicsComponentRef physics, GraphicsComponentRef graphics) 
	: GameObject(std::move(physics), std::move(graphics))
{
	_input = std::move(input);
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

