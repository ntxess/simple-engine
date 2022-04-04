#pragma once
#include <SFML/Graphics.hpp>

#include "Command.hpp"

class Command;

typedef std::shared_ptr<Command> CommandRef;

class InputComponent
{
public:
	virtual const CommandRef& GetCommand() const = 0;
	virtual sf::Vector2f GetDirection() const = 0;
	virtual void Update(const sf::Event& event) = 0;
};
