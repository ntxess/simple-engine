#include "PlayerInput.hpp"

PlayerInput::PlayerInput()
	: _direction(sf::Vector2f(0, 0))
{
	ResetCommandBinds();
}

PlayerInput::~PlayerInput()
{}

const CommandRef& PlayerInput::GetCommand() const
{
	return _command;
}

sf::Vector2f PlayerInput::GetDirection() const
{
	return _direction;
}

void PlayerInput::ResetCommandBinds()
{
	_KeyLShift = std::make_shared<CommandDodge>();
	_KeyRShift = std::make_shared<CommandExSkill>();
}

void PlayerInput::Update(const sf::Event& event)
{
	_command = NULL;
	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::LShift)
			_command = _KeyLShift;

		if (event.key.code == sf::Keyboard::RShift)
			_command = _KeyRShift;
	}

	const float input = 1.f;
	_direction = sf::Vector2f(0, 0);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		_direction.y -= input;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		_direction.x -= input;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		_direction.y += input;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		_direction.x += input;
}
