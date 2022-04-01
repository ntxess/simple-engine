#include "PlayerInput.hpp"

PlayerInput::PlayerInput()
{
	ResetCommandBinds();
}

PlayerInput::~PlayerInput()
{}

void PlayerInput::ResetCommandBinds()
{
	_KeyShift = std::make_shared<CommandDodge>();
	_KeySpace = std::make_shared<CommandEXSkill>();
}

void PlayerInput::Update(sf::Event event)
{
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
	
	_command = NULL;
	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::Space)
			_command = _KeySpace;

		if (event.key.code == sf::Keyboard::LShift)
			_command = _KeyShift;
	}
}
