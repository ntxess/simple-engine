#include "GameObject.hpp"

GameObject::GameObject() :
	_input(nullptr),
	_physics(nullptr),
	_graphics(nullptr),
	_velocity(0),
	_x(0),
	_y(0) {}

GameObject::GameObject(InputComponent* input, PhysicsComponent* physics, GraphicsComponent* graphics) :
	_input(input),
	_physics(physics),
	_graphics(graphics),
	_velocity(0),
	_x(0),
	_y(0) {}

GameObject::~GameObject()
{
	delete _input;
	delete _physics;
	delete _graphics;
}

InputComponent* GameObject::Input()
{
	return _input;
}

PhysicsComponent* GameObject::Physics()
{
	return _physics;
}

GraphicsComponent* GameObject::Graphics()
{
	return _graphics;
}

void GameObject::Update()
{
	if(_graphics)
		_graphics->Update();
	if(_physics)
		_physics->Update();
}

void GameObject::Render(sf::RenderTarget* rt, double interpolation)
{
	if(_graphics)
		_graphics->Render(rt, interpolation);
}

