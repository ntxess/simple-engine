#pragma once
#include <SFML/Graphics.hpp>

#include "Command.hpp"

typedef std::shared_ptr<Command> CommandRef;

class PlayerInput
{
	friend class PlayerPhysics;
	friend class PlayerGraphics;

private:
	sf::Vector2f _direction;

	CommandRef _command;
	CommandRef _KeyLShift;
	CommandRef _KeyRShift;

public:
	PlayerInput();
	~PlayerInput();

	void ResetCommandBinds();
 	void Update(sf::Event event);
};

