#pragma once
#include <SFML/Graphics.hpp>

#include "CommandDodge.hpp"
#include "CommandEXSkill.hpp"

class PlayerInput
{
private:
	sf::Vector2f _direction; 

	std::shared_ptr<Command> _command;
	std::shared_ptr<Command> _KeyLShift;
	std::shared_ptr<Command> _KeyRShift;

public:
	PlayerInput();
	~PlayerInput();

	const std::shared_ptr<Command>& GetCommand() const;
	sf::Vector2f GetDirection() const;
	void ResetCommandBinds();
 	void Update(const sf::Event& event);
};

