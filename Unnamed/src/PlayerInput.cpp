#include "PlayerInput.hpp"

PlayerInput::PlayerInput() : _direction(sf::Vector2f(0,0))
{}

PlayerInput::~PlayerInput()
{}

sf::Vector2f PlayerInput::GetDirection()
{
	return _direction;
}

void PlayerInput::ClearDirection()
{
	_direction = sf::Vector2f(0, 0);
}

void PlayerInput::Move(sf::Vector2f direction)
{
	_direction += direction;
	_direction.x = std::min(std::max(_direction.x, -1.0f), 1.0f);
	_direction.y = std::min(std::max(_direction.y, -1.0f), 1.0f);
}