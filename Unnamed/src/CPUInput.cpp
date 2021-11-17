#include "CPUInput.hpp"

CPUInput::CPUInput() : _direction(sf::Vector2f(0, 0))
{
	_previousD.x = -1;
	_previousD.y = 1;
}

CPUInput::~CPUInput()
{}

const sf::Vector2f& CPUInput::GetDirection()
{
	return _direction;
}

void CPUInput::Move(sf::Vector2f direction)
{
	if (_previousD.x == -1 && _previousD.y == 1)
	{
		_direction.x = -1;
		_direction.y = -1;
	}

	if (_previousD.x == -1 && _previousD.y == -1)
	{
		_direction.x = 1;
		_direction.y = -1;
	}

	if (_previousD.x == 1 && _previousD.y == -1)
	{
		_direction.x = 1;
		_direction.y = 1;
	}

	if (_previousD.x == 1 && _previousD.y == 1)
	{
		_direction.x = -1;
		_direction.y = 1;
	}
	_previousD.x = _direction.x;
	_previousD.y = _direction.y;
}

void CPUInput::ClearDirection()
{
	_direction = sf::Vector2f(0, 0);
}