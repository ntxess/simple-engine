#include "InputComponent.hpp"

InputComponent::InputComponent() : _direction(sf::Vector2f(0, 0))
{}

InputComponent::~InputComponent()
{}

const sf::Vector2f& InputComponent::GetDirection()
{
	return _direction;
}

void InputComponent::Update(sf::Vector2f direction)
{
	_direction += direction;
}

void InputComponent::ClearDirection()
{
	_direction = sf::Vector2f(0, 0);
}
