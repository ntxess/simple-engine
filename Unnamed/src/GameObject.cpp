#include "GameObject.hpp"

Identity::Identity()
	: _input(nullptr), _physics(nullptr), _graphics(nullptr), _velocity(1.f), _isTouched(false)
{}

Identity::Identity(thor::ResourceHolder<sf::Texture, std::string>& holder, std::string ID) 
	: _input(nullptr), _physics(nullptr), _graphics(nullptr), _velocity(1.f), _isTouched(false)
{
	sf::Texture& texture = holder[ID];
	_sprite.setTexture(texture);
	_sprite.setScale(sf::Vector2f(1, 1));
	std::cout << "TEXTURE LOADED: " << ID << std::endl;
}

Identity::~Identity()
{}

InputComponentRef& Identity::GetInput()
{
	return _input;
}

PhysicsComponentRef& Identity::GetPhysics()
{
	return _physics;
}

GraphicsComponentRef& Identity::GetGraphics()
{
	return _graphics;
}

bool Identity::IsTouched()
{
	return _isTouched;
}

const sf::Sprite& Identity::GetSprite()
{
	return _sprite;
}

const sf::Vector2f& Identity::GetPosition()
{
	return _sprite.getPosition();
}

void Identity::SetInput(InputComponentRef& input)
{
	_input = std::move(input);
}

void Identity::SetPhysics(PhysicsComponentRef& physics)
{
	_physics = std::move(physics);
}

void Identity::SetGraphics(GraphicsComponentRef& graphics)
{
	_graphics = std::move(graphics);
}

void Identity::SetVelocity(float velocity)
{
	_velocity = velocity;
}

void Identity::SetTouchTag(bool isTouched)
{
	_isTouched = isTouched;
}

void Identity::SetScale(sf::Vector2f scale)
{
	_sprite.setScale(scale);
}

void Identity::SetPosition(sf::Vector2f position)
{
	_sprite.setPosition(position);
}

void Identity::AddAnimation(const std::string& id, const thor::FrameAnimation& animation, sf::Time duration)
{
	_graphics->GetAnimator().addAnimation(id, animation, duration);
}

void Identity::Update(float deltaTime)
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

void Identity::Render(RenderWindowRef& rw, float interpolation)
{
	rw->draw(_sprite);
}

