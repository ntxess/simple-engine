#include "Component.hpp"

Component::Component()
	: _input(nullptr), _physics(nullptr), _graphics(nullptr), _velocity(1.f), _isTouched(false)
{}

Component::Component(thor::ResourceHolder<sf::Texture, std::string>& holder, std::string ID) 
	: _input(nullptr), _physics(nullptr), _graphics(nullptr), _velocity(1.f), _isTouched(false)
{
	sf::Texture& texture = holder[ID];
	_sprite.setTexture(texture);
	_sprite.setScale(sf::Vector2f(1, 1));
	std::cout << "TEXTURE LOADED: " << ID << std::endl;
}

Component::~Component()
{}

InputComponentRef& Component::GetInput()
{
	return _input;
}

PhysicsComponentRef& Component::GetPhysics()
{
	return _physics;
}

GraphicsComponentRef& Component::GetGraphics()
{
	return _graphics;
}

bool Component::IsTouched()
{
	return _isTouched;
}

const sf::Sprite& Component::GetSprite()
{
	return _sprite;
}

const sf::Vector2f& Component::GetPosition()
{
	return _sprite.getPosition();
}

void Component::SetInput(InputComponentRef& input)
{
	_input = std::move(input);
}

void Component::SetPhysics(PhysicsComponentRef& physics)
{
	_physics = std::move(physics);
}

void Component::SetGraphics(GraphicsComponentRef& graphics)
{
	_graphics = std::move(graphics);
}

void Component::SetVelocity(float velocity)
{
	_velocity = velocity;
}

void Component::SetTouchTag(bool isTouched)
{
	_isTouched = isTouched;
}

void Component::SetScale(sf::Vector2f scale)
{
	_sprite.setScale(scale);
}

void Component::SetPosition(sf::Vector2f position)
{
	_sprite.setPosition(position);
}

void Component::AddAnimation(const std::string& id, const thor::FrameAnimation& animation, sf::Time duration)
{
	_graphics->GetAnimator().addAnimation(id, animation, duration);
}

void Component::Update(float deltaTime)
{	
	sf::Vector2f direction(0.f, 0.f);
	if (_input)
	{
		direction.x = _input->GetDirection().x * _velocity;
		direction.y = _input->GetDirection().y * _velocity;
		_input->ClearDirection();
	}

	if (_physics)
	{
		_physics->Update(_sprite, direction, deltaTime);
	}

	if (_graphics)
	{
		_graphics->Update(direction, deltaTime);
		_graphics->GetAnimator().animate(_sprite);
	}
}

void Component::Render(RenderWindowRef& rw, float interpolation)
{
	rw->draw(_sprite);
}

