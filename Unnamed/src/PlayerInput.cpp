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
	_direction = direction;
	std::cout << "x: " << _direction.x << " y: " << _direction.y << std::endl;
}