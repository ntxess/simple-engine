#include "AIInput.hpp"

AIInput::AIInput()
	: _moveLeft(false)
	, _moveRight(false)
{}

AIInput::~AIInput()
{}

const std::shared_ptr<Command>& AIInput::GetCommand() const
{
	return _command;
}

sf::Vector2f AIInput::GetDirection() const
{
	return _direction;
}

void AIInput::Update(const sf::Event& event)
{
	const float input = 1.f;
	_direction = sf::Vector2f(0, 0);

	if (!_moveLeft)
	{
		_direction.x -= input;
		//_moveLeft = true;
		//_moveRight = false;
	}
	//else if(!_moveRight)
	//{
	//	_direction.x += input;
	//	_moveRight = true;
	//	_moveLeft = false;
	//}
}
