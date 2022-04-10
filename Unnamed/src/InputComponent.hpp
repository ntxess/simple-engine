#pragma once
#include <SFML/Graphics.hpp>

#include "Command.hpp"

class InputComponent
{
public:
	virtual const std::shared_ptr<Command>& GetCommand() const = 0;
	virtual sf::Vector2f GetDirection() const = 0;
	virtual void Update(const sf::Event& event) = 0;
};
