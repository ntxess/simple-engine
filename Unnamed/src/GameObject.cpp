#include "GameObject.hpp"

GameObject::GameObject()
	: _velocity(1),
	_input(nullptr),
	_physics(nullptr),
	_graphics(nullptr)
{}

GameObject::GameObject(GraphicsComponentRef graphics)
	: _velocity(320.25),
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

const sf::Vector2f& GameObject::GetDirection()
{
	return _input->GetDirection();
}

const sf::Vector2f& GameObject::GetPosition()
{
	return _graphics->GetSprite().getPosition();
}

void GameObject::SetVelocity(float velocity)
{
	_velocity = velocity;
}

void GameObject::SetScale(sf::Vector2f scale)
{
	_graphics->GetSprite().setScale(scale);
	_graphics->GetSprite().setTextureRect(_graphics->GetSprite().getTextureRect());
}

void GameObject::SetPosition(sf::Vector2f position)
{
	_graphics->GetSprite().setPosition(position);
}

void GameObject::PlayAnimation(const std::string& id, bool loop)
{
	_graphics->GetAnimator().playAnimation(id, loop);
}

void GameObject::AddAnimation(const std::string& id, const thor::FrameAnimation& animation, sf::Time duration)
{
	_graphics->GetAnimator().addAnimation(id, animation, duration);
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

