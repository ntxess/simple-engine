#include "GameObject.hpp"

GameObject::GameObject()
	: _input(nullptr)
	, _physics(nullptr)
	, _graphics(nullptr)
	, _velocity(1.f)
	, _isTouched(false)
{}

GameObject::GameObject(thor::ResourceHolder<sf::Texture, std::string>& holder, std::string ID) 
	: _input(nullptr)
	, _physics(nullptr)
	, _graphics(nullptr)
	, _velocity(1.f)
	, _isTouched(false)
{
	sf::Texture& texture = holder[ID];
	_sprite.setTexture(texture);
	_sprite.setScale(sf::Vector2f(1, 1));
	std::cout << "TEXTURE LOADED: " << ID << std::endl;
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

bool GameObject::IsTouched()
{
	return _isTouched;
}

const sf::Sprite& GameObject::GetSprite()
{
	return _sprite;
}

const sf::Vector2f& GameObject::GetPosition()
{
	return _sprite.getPosition();
}

void GameObject::SetInput(InputComponentRef& input)
{
	_input = std::move(input);
}

void GameObject::SetPhysics(PhysicsComponentRef& physics)
{
	_physics = std::move(physics);
}

void GameObject::SetGraphics(GraphicsComponentRef& graphics)
{
	_graphics = std::move(graphics);
}

void GameObject::SetVelocity(float velocity)
{
	_velocity = velocity;
}

void GameObject::SetTouchTag(bool isTouched)
{
	_isTouched = isTouched;
}

void GameObject::SetScale(sf::Vector2f scale)
{
	_sprite.setScale(scale);
}

void GameObject::SetPosition(sf::Vector2f position)
{
	_sprite.setPosition(position);
}

void GameObject::SetOrigin(sf::Vector2f position)
{
	_sprite.setOrigin(position);
}

void GameObject::Update(const float& deltaTime)
{	
	sf::Vector2f direction(0.f, 0.f);
	if (_input)
	{
		direction.x = _input->GetDirection().x * _velocity;
		direction.y = _input->GetDirection().y * _velocity;
		_input->ClearDirection();
	}

	if (_physics)
		_physics->Update(_sprite, direction, deltaTime);

	if (_graphics)
		_graphics->Update(_sprite, direction, deltaTime);
}

void GameObject::Render(const RenderWindowRef& rw, const float& interpolation)
{
	rw->draw(_sprite);
}

