#include "GameObject.hpp"

GameObject::GameObject()
	: _velocity(1),
	_input(nullptr),
	_physics(nullptr),
	_graphics(nullptr)
{}

GameObject::GameObject(GraphicsComponentRef graphics)
	: _velocity(350),
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

InputComponentRef& GameObject::GetInput()
{
	return _input;
}

PhysicsComponentRef& GameObject::GetPhysics()
{
	return _physics;
}

GraphicsComponentRef& GameObject::GetGraphics()
{
	return _graphics;
}

void GameObject::Update(float deltaTime)
{
	if(_physics)
		_physics->Update(deltaTime);

	if (_graphics)
	{
		if (_input)
		{
			_graphics->Update(_input->GetDirection(), _velocity, deltaTime);
			_input->ClearDirection();
		}
		else
		{
			_graphics->Update(deltaTime);
		}
	}
}

void GameObject::Render(RenderWindowRef& rw, float interpolation)
{
	if(_graphics)
		_graphics->Render(rw, interpolation);
}

