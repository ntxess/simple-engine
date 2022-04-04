#pragma once
#include <SFML/Graphics.hpp>

#include "InputComponent.hpp"
#include "CommandDodge.hpp"
#include "CommandEXSkill.hpp"

typedef std::shared_ptr<Command> CommandRef;

class PlayerInput : public InputComponent
{
private:
	sf::Vector2f _direction; 

	CommandRef _command;
	CommandRef _KeyLShift;
	CommandRef _KeyRShift;

public:
	PlayerInput();
	~PlayerInput();

	const CommandRef& GetCommand() const;
	sf::Vector2f GetDirection() const;
	void ResetCommandBinds();
 	void Update(const sf::Event& event);
};

