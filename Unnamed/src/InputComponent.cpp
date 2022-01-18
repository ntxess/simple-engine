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
	_direction.x = std::min(std::max(_direction.x, -1.0f), 1.0f);
	_direction.y = std::min(std::max(_direction.y, -1.0f), 1.0f);
}

void InputComponent::ClearDirection()
{
	_direction = sf::Vector2f(0, 0);
}
